#ifndef BARBARIAN_APPLICATION_H_ 
#define BARBARIAN_APPLICATION_H_

#include "include/cef_app.h"

namespace Barbarian {

class BBApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {

	public:
		BBApp();

		void SetSubprocess(char *_subprocess_path);

	private:

		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
			OVERRIDE { return this; }

		virtual void OnContextInitialized() OVERRIDE;
		virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;
		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
										CefRefPtr<CefFrame> frame,
										CefRefPtr<CefV8Context> context) OVERRIDE;

		// Registers custom schemes
		virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) OVERRIDE;

		char *subprocess_path;

		IMPLEMENT_REFCOUNTING(BBApp);
};

}

#endif
