#ifndef BARBARIAN_APPLICATION_H_ 
#define BARBARIAN_APPLICATION_H_

#include "include/cef_app.h"

class BBApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {

	public:
		BBApp();

	private:
		IMPLEMENT_REFCOUNTING(BBApp);
};

#endif
