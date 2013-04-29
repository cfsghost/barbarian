#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"

#include "barbarian.hpp"
#include "client.hpp"

BBClient::BBClient()
{
    
}

CefRefPtr<CefLoadHandler> BBClient::GetLoadHandler()
{
	return this;
}

void BBClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
	REQUIRE_UI_THREAD();
}

void BBClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	REQUIRE_UI_THREAD();

	GtkWidget* window = gtk_widget_get_ancestor(
		GTK_WIDGET(browser->GetHost()->GetWindowHandle()),
		GTK_TYPE_WINDOW);

	std::string titleStr(title);

	gtk_window_set_title(GTK_WINDOW(window), titleStr.c_str());
}
