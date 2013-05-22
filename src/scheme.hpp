#ifndef BARBARIAN_SCHEME_H_
#define BARBARIAN_SCHEME_H_

#include "include/cef_resource_handler.h"
#include "include/cef_response.h"
#include "include/cef_scheme.h"

namespace Barbarian {

//class BBSchemeHandler : public CefResourceHandler {
class BBSchemeHandler : public CefResourceHandler {

	public:
		BBSchemeHandler();

		// CefResourceHandler Methods
		virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) OVERRIDE;
		virtual void Cancel() OVERRIDE {
			REQUIRE_IO_THREAD();
		}

		virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
										int64& response_length,
										CefString& redirectUrl) OVERRIDE;

		virtual bool ReadResponse(void* data_out,
									int bytes_to_read,
									int& bytes_read,
									CefRefPtr<CefCallback> callback) OVERRIDE;

		void SetContent(std::string data);
		void SetMIMEType(std::string mime_type);

	private:
		std::string data_;
		std::string mime_type_;
		size_t offset_;

		IMPLEMENT_REFCOUNTING(BBSchemeHandler);
		IMPLEMENT_LOCKING(BBSchemeHandler);
};

class BBSchemeHandlerFactory : public CefSchemeHandlerFactory {
	public:

		virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
														CefRefPtr<CefFrame> frame,
														const CefString& scheme_name,
														CefRefPtr<CefRequest> request) OVERRIDE {
			REQUIRE_IO_THREAD();

			return new BBSchemeHandler();
		}
 
	   IMPLEMENT_REFCOUNTING(BBSchemeHandlerFactory);
};

}

#endif
