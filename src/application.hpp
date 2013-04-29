#ifndef BARBARIAN_APPLICATION_H_ 
#define BARBARIAN_APPLICATION_H_

#include "include/cef_app.h"

class BBApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {

	public:
		BBApp();

		void SetSubprocess(char *_subprocess_path);

	private:

		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
			OVERRIDE { return this; }

		virtual void OnContextInitialized() OVERRIDE;
		virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

		char *subprocess_path;

		IMPLEMENT_REFCOUNTING(BBApp);
};

#endif
