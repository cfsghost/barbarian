#include <v8.h>
#include <node.h>

#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"

#include "barbarian.hpp"
#include "client.hpp"

const char internalURLPrefix[] = "barbarian://";

namespace Barbarian {

	using namespace node;
	using namespace v8;

	BBClient::BBClient()
	{

	}

	void BBClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
	{
		REQUIRE_UI_THREAD();
	}

	void BBClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
	{
		REQUIRE_UI_THREAD();

		GtkWidget* window = gtk_widget_get_ancestor(
			GTK_WIDGET(browser->GetHost()->GetWindowHandle()),
			GTK_TYPE_WINDOW);

		std::string titleStr(title);

		gtk_window_set_title(GTK_WINDOW(window), titleStr.c_str());
	}

	CefRefPtr<CefResourceHandler> BBClient::GetResourceHandler(
										CefRefPtr<CefBrowser> browser,
										CefRefPtr<CefFrame> frame,
										CefRefPtr<CefRequest> request)
	{
		std::string url = request->GetURL();

		return NULL;
	}

	void BBClient::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
													const CefString &url,
													bool &allow_os_execution)
	{
		std::string urlStr = url;

		if (urlStr.find(internalURLPrefix) == 0) {

			if (internal_request_handler == NULL)
				return;

			// Preparing protocol object
			Local<Object> protocol = Object::New();
			protocol->Set(String::NewSymbol("url"), String::New(urlStr.c_str()));

			// Preparing arguments
			Local<Value> argv[1] = {
				protocol
			};

			allow_os_execution = true;
			internal_request_handler->cb->Call(internal_request_handler->Holder, 1, argv);
		}
	}
}
