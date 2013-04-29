#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"

#include "application.hpp"

BBApp::BBApp()
{
}

void BBApp::OnContextInitialized()
{
	printf("OnContextInitialized\n");
}

void BBApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{
	printf("12312312312312909999\n");
//	printf("======== %s\n", command_line->GetProgram().ToString().c_str());
	command_line->SetProgram(CefString("/home/fred/opensource-work/barbarian/build/Release/subprocess.node"));
	printf("======== %s\n", command_line->GetCommandLineString().ToString().c_str());
}
