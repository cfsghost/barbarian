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
		offset_ = 0;
	}

	void BBSchemeHandler::SetContent(std::string data)
	{
		data_ = data;
	}

	void BBSchemeHandler::SetMIMEType(std::string mime_type)
	{
		mime_type_ = mime_type;
	}

	void BBSchemeHandler::SetStatus(int status)
	{
		status_ = status;
	}

	bool BBSchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
	{
		REQUIRE_IO_THREAD();

		AutoLock lock_scope(this);

		std::string url = request->GetURL();

		if (url.find(internalURLPrefix) == 0) {

			if (internal_request_handler == NULL)
				return false;

			// Default status
			offset_ = 0;
			mime_type_ = "text/html";
			data_ = "";
			status_ = 200;

			// Preparing event message to JavaScript environment
			BBEventMessage *message = new BBEventMessage();
			message->event = BB_EVENT_REQUEST;
			message->callback = callback;
			message->request = request;
			message->userdata = (void *)this;
			async->data = (void *)message;
			uv_async_send(async);

			return true;
		}

		return false;
	}

	void BBSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response,
							int64& response_length,
							CefString& redirectUrl)
	{
		REQUIRE_IO_THREAD();
		printf("GetResponseHeaders\n");

		response->SetMimeType(mime_type_);
		response->SetStatus(status_);

		// Set the resulting response length
		response_length = data_.length();
	}

	bool BBSchemeHandler::ReadResponse(void *data_out,
						int bytes_to_read,
						int& bytes_read,
						CefRefPtr<CefCallback> callback)
	{
		REQUIRE_IO_THREAD();
		printf("ReadResponse\n");

		bool has_data = false;
		bytes_read = 0;

		AutoLock lock_scope(this);

		if (offset_ < data_.length()) {

			int transfer_size = (std::min)(bytes_to_read, static_cast<int>(data_.length() - offset_));
			memcpy(data_out, data_.c_str() + offset_, transfer_size);
			offset_ += transfer_size;
			bytes_read = transfer_size;
			has_data = true;
		}


		return has_data;
	}
}
