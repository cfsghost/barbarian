#include <v8.h>
#include <node.h>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_runnable.h"

#include "barbarian.hpp"
#include "application.hpp"
#include "client.hpp"
#include "scheme.hpp"

namespace Barbarian {
 
	using namespace node;
	using namespace v8;

	CefSettings settings;
	CefMainArgs mainArgs;
	CefRefPtr<BBApp> app;

	NodeCallback *internal_request_handler = NULL;
	uv_async_t *async = new uv_async_t;

	static uv_timer_t messageLoop;

	void messageLoop_cb(uv_timer_t *handle, int status)
	{
		CefDoMessageLoopWork();
	}

	void InternalEventHandler(uv_async_t *handle, int status)
	{
		HandleScope scope;
		BBEventMessage *message = (BBEventMessage *)(handle->data);
		std::string url = message->request->GetURL();

		// Make a new object for JavaScript
		Local<Object> event = Object::New();
		event->Set(String::NewSymbol("event"), Integer::New(message->event));
		event->Set(String::NewSymbol("url"), String::New(url.c_str()));

		if (message->callback) {

			Handle<ObjectTemplate> templ = ObjectTemplate::New();
			templ->SetInternalFieldCount(2);

			Local<Object> obj = templ->NewInstance();
			obj->SetInternalField(0, External::New(message->userdata));
			obj->SetInternalField(1, External::New(message->callback));

			event->Set(String::NewSymbol("callback"), obj);
		}

		// Preparing arguments
		Local<Value> argv[1] = {
			event
		};

		internal_request_handler->cb->Call(internal_request_handler->Holder, 1, argv);

		delete message;
	}

	static Handle<Value> CefInit(const Arguments& args)
	{
		HandleScope scope;
		char *subprocess_path = strdup(*String::Utf8Value(args[0]->ToString()));

		mainArgs = CefMainArgs(0, NULL);
		app = new BBApp;
		app->SetSubprocess(subprocess_path);

		gtk_init(NULL, NULL);

		// Setting paths
		settings.multi_threaded_message_loop = false;
		CefString(&settings.browser_subprocess_path) = subprocess_path;
		CefString(&settings.resources_dir_path) = strdup(*String::Utf8Value(args[1]->ToString()));
		CefString(&settings.locales_dir_path) = strdup(*String::Utf8Value(args[2]->ToString()));

		CefInitialize(mainArgs, settings, app.get());

		// Integrate CEF message loop to uv
		uv_timer_init(uv_default_loop(), &messageLoop);
		uv_timer_start(&messageLoop, messageLoop_cb, 0, 1);
		uv_async_init(uv_default_loop(), async, InternalEventHandler);

		CefRegisterSchemeHandlerFactory("barbarian", "content", new BBSchemeHandlerFactory());

		return Undefined();
	}

	static Handle<Value> CreateWindow(const Arguments& args)
	{
		HandleScope scope;
		CefRefPtr<CefBrowser> browser;
		CefBrowserSettings browserSettings;
		CefWindowInfo windowInfo;

		// Process arguments
		String::Utf8Value url(args[0]);

		// Window
		GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "Barbarian");
		gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

		// Container
		GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
		gtk_container_add(GTK_CONTAINER(window), vbox);

		// Create client
		CefRefPtr<BBClient> client(new BBClient);

		windowInfo.SetAsChild(vbox);

		//browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), CefString(*url), browserSettings);
		CefBrowserHost::CreateBrowser(windowInfo, client.get(), CefString(*url), browserSettings);

		gtk_widget_show_all(GTK_WIDGET(window));

		printf("CreateWindow %d\n", PID_BROWSER);

		return Undefined();
	}

	static Handle<Value> SetEventHandler(const Arguments& args)
	{
		HandleScope scope;

		if (!args[0]->IsFunction()) {
			return Undefined();
		}

		if (internal_request_handler) {
			internal_request_handler->Holder.Dispose();
			internal_request_handler->cb.Dispose();
		} else {
			internal_request_handler = new NodeCallback;
		}

		internal_request_handler->Holder = Persistent<Object>::New(args.Holder());
		internal_request_handler->cb = Persistent<Function>::New(Handle<Function>::Cast(args[0]));

		return Undefined();
	}

	static Handle<Value> RunCallback(const Arguments& args)
	{
		HandleScope scope;

		Local<External> wrap = Local<External>::Cast(args[0]->ToObject()->GetInternalField(1));
		CefRefPtr<CefCallback> callback = (CefCallback *)(wrap->Value());

		callback->Continue();

		return Undefined();
	}

	static Handle<Value> SetContent(const Arguments& args)
	{
		HandleScope scope;

		Local<External> wrap = Local<External>::Cast(args[0]->ToObject()->GetInternalField(0));
		BBSchemeHandler *scheme = (BBSchemeHandler *)(wrap->Value());

		scheme->SetContent(*String::Utf8Value(args[1]->ToString()));

		return Undefined();
	}

	static void init(Handle<Object> target) {
		HandleScope scope;

		NODE_SET_METHOD(target, "init", CefInit);
		NODE_SET_METHOD(target, "createWindow", CreateWindow);
		NODE_SET_METHOD(target, "setEventHandler", SetEventHandler);
		NODE_SET_METHOD(target, "runCallback", RunCallback);
		NODE_SET_METHOD(target, "setContent", SetContent);
	}

	NODE_MODULE(barbarian, init);
}
