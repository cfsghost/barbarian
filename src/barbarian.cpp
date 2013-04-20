#include <v8.h>
#include <node.h>

#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_runnable.h"
#include "barbarian.hpp"

namespace Barbarian {
 
	using namespace node;
	using namespace v8;

	static void init(Handle<Object> target) {
		HandleScope scope;
	}

	NODE_MODULE(barbarian, init);
}
