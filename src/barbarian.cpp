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

	static Handle<Value> CefInit(const Arguments& args)
	{
		HandleScope scope;
		CefRefPtr<BBApp> app(new BBApp);
		CefSettings settings;
		CefMainArgs mainArgs(0, NULL);

		// Setting paths
		CefString(&settings.resources_dir_path) = *String::Utf8Value(args[0]->ToString());
		CefString(&settings.locales_dir_path) = *String::Utf8Value(args[1]->ToString());

		CefInitialize(mainArgs, settings, app.get());

		return Undefined();
	}

	static Handle<Value> CreateWindow(const Arguments& args)
	{
		HandleScope scope;
		CefRefPtr<CefBrowser> browser;
		CefRefPtr<BBClient> client(new BBClient);
		CefWindowInfo windowInfo;

		browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), CefString("http://www.google.com"), CefBrowserSettings());

		CefRunMessageLoop();

		return Undefined();
	}

	static void init(Handle<Object> target) {
		HandleScope scope;

		NODE_SET_METHOD(target, "init", CefInit);
		NODE_SET_METHOD(target, "createWindow", CreateWindow);
	}

	NODE_MODULE(barbarian, init);
}
