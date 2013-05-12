#ifndef BARBARIAN_CLIENT_H_ 
#define BARBARIAN_CLIENT_H_

#include "include/cef_client.h"

namespace Barbarian {

class BBClient : public CefClient, public CefLoadHandler, public CefDisplayHandler, public CefRequestHandler {

	public:
		BBClient();

		// BBClient methods
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
			return this;
		}

		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE {
			return this;
		}

		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

		// CefRequestHandler Methods
		virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
												CefRefPtr<CefBrowser> browser,
												CefRefPtr<CefFrame> frame,
												CefRefPtr<CefRequest> request) OVERRIDE;

		virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
												const CefString& url,
												bool &allow_os_execution) OVERRIDE;

	private:

		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()
			OVERRIDE { return this; }

		IMPLEMENT_REFCOUNTING(BBClient);
};

}

#endif
