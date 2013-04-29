
#include "include/cef_app.h"
#include "include/cef_browser.h"

#if defined(OS_WIN)

#include <windows.h>
int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow) 
                                         
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	CefMainArgs mainArgs(hInstance);
}

#else

int main(int argc, char **argv)
{
	CefMainArgs mainArgs(argc, argv);

	int exit_code = CefExecuteProcess(mainArgs, NULL);

	return exit_code;
}

#endif
