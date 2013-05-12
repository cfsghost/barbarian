#include <v8.h>
#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"

#include "application.hpp"

BBApp::BBApp()
{
}

void BBApp::SetSubprocess(char *_subprocess_path)
{
	subprocess_path = _subprocess_path;
}

void BBApp::OnContextInitialized()
{
	printf("OnContextInitialized\n");
}

void BBApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{
	command_line->SetProgram(CefString(subprocess_path));
}

void BBApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	CefRefPtr<CefV8Value> object = context->GetGlobal();
}
