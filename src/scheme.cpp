#include <v8.h>
#include <node.h>

#include "barbarian.hpp"
#include "scheme.hpp"

const char internalURLPrefix[] = "barbarian://";

namespace Barbarian {

	using namespace node;
	using namespace v8;

	BBSchemeHandler::BBSchemeHandler()
	{

	}

	bool BBSchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
	{
		REQUIRE_IO_THREAD();

		return false;
	}

	void BBSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
							int64& response_length,
							CefString& redirectUrl)
	{
		REQUIRE_IO_THREAD();
	}

	bool BBSchemeHandler::ReadResponse(void* data_out,
						int bytes_to_read,
						int& bytes_read,
						CefRefPtr<CefCallback> callback)
	{
		REQUIRE_IO_THREAD();

		return false;
	}
}
