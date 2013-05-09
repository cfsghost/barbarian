#include <v8.h>
#include <node.h>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_runnable.h"

#include "barbarian.hpp"
#include "application.hpp"
#include "client.hpp"

namespace Barbarian {
 
	using namespace node;
	using namespace v8;

	CefSettings settings;
	CefMainArgs mainArgs;
	CefRefPtr<BBApp> app;

	static uv_timer_t messageLoop;

	void messageLoop_cb(uv_timer_t *handle, int status)
	{
		CefDoMessageLoopWork();
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

		browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), CefString(*url), browserSettings);

		gtk_widget_show_all(GTK_WIDGET(window));

		return Undefined();
	}

	static void init(Handle<Object> target) {
		HandleScope scope;

		NODE_SET_METHOD(target, "init", CefInit);
		NODE_SET_METHOD(target, "createWindow", CreateWindow);
	}

	NODE_MODULE(barbarian, init);
}
