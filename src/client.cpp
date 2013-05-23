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

	void BBClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		m_browser = browser;

		// Preparing event message to JavaScript environment
		BBEventMessage *message = new BBEventMessage();
		message->event = BB_EVENT_WINDOW_CREATED;
		message->browser = browser;
		message->userdata = (void *)this;

		uv_async_t *async = new uv_async_t;
		async->data = (void *)message;
		uv_async_init(uv_default_loop(), async, InternalEventHandler);
		uv_async_send(async);
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
		REQUIRE_UI_THREAD();
		std::string url = request->GetURL();

		if (url.find(internalURLPrefix) == 0) {

			if (internal_request_handler == NULL)
				return NULL;
		}

		return NULL;
	}

	bool BBClient::OnBeforeResourceLoad(
							CefRefPtr<CefBrowser> browser,
							CefRefPtr<CefFrame> frame,
							CefRefPtr<CefRequest> request)
	{
		REQUIRE_UI_THREAD();
//		HandleScope scope;
		std::string url = request->GetURL();
//		printf("======= %s\n", url.c_str());

		if (internal_request_handler == NULL)
			return false;

		return false;
	}

	void BBClient::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
													const CefString &url,
													bool &allow_os_execution)
	{
		std::string urlStr = url;
		//printf("=======--- %s\n", urlStr.c_str());
/*
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
*/
	}

	void BBClient::OnLoadError(CefRefPtr<CefBrowser> browser,
									CefRefPtr<CefFrame> frame,
									ErrorCode errorCode,
									const CefString& errorText,
									const CefString& failedUrl)
	{
		if (errorCode == ERR_UNKNOWN_URL_SCHEME) {
			return;
		}
	}

}
