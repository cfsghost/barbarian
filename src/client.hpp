#ifndef BARBARIAN_CLIENT_H_ 
#define BARBARIAN_CLIENT_H_

#include "include/cef_client.h"

class BBClient : public CefClient, public CefLoadHandler {

	public:
		BBClient();

	private:
		IMPLEMENT_REFCOUNTING(BBClient);
};

#endif
