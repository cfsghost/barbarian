#ifndef BARBARIAN_CLIENT_H_ 
#define BARBARIAN_CLIENT_H_

#include "include/cef_client.h"

class BBClient : public CefClient, public CefLoadHandler, public CefDisplayHandler {

	public:
		BBClient();
		CefRefPtr<CefLoadHandler> GetLoadHandler();
		void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
		void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);

	private:

		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()
			OVERRIDE { return this; }

		IMPLEMENT_REFCOUNTING(BBClient);
};

#endif
