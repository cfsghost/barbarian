#ifndef BARBARIAN_CLIENT_H_ 
#define BARBARIAN_CLIENT_H_

#include <v8.h>
#include "include/cef_client.h"

namespace Barbarian {

class BBClient : public CefClient,
					public CefLifeSpanHandler,
					public CefLoadHandler,
					public CefDisplayHandler,
					public CefRequestHandler {

	public:
		BBClient();

		CefRefPtr<CefBrowser> GetBrowser() { return m_browser; }

		// BBClient methods
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
			return this;
		}

		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE {
			return this;
		}

		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

		// CefLifeSpanHandler Methods
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

		// CefRequestHandler Methods
		virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
												CefRefPtr<CefBrowser> browser,
												CefRefPtr<CefFrame> frame,
												CefRefPtr<CefRequest> request) OVERRIDE;
		virtual bool OnBeforeResourceLoad(
									CefRefPtr<CefBrowser> browser,
									CefRefPtr<CefFrame> frame,
									CefRefPtr<CefRequest> request) OVERRIDE;

		virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
												const CefString& url,
												bool &allow_os_execution) OVERRIDE;

		// CefLoadHandler Methods
		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
										CefRefPtr<CefFrame> frame,
										ErrorCode errorCode,
										const CefString& errorText,
										const CefString& failedUrl) OVERRIDE;

	private:

		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
			return this;
		}

		IMPLEMENT_REFCOUNTING(BBClient);

	protected:
		CefRefPtr<CefBrowser> m_browser;
};

}

#endif
