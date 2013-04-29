#ifndef BARBARIAN_APPLICATION_H_ 
#define BARBARIAN_APPLICATION_H_

#include "include/cef_app.h"

class BBApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {

	public:
		BBApp();

	private:

		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
			OVERRIDE { return this; }

		virtual void OnContextInitialized() OVERRIDE;
		virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

		IMPLEMENT_REFCOUNTING(BBApp);
};

#endif
