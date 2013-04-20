#include <v8.h>
#include <node.h>

#include "barbarian.hpp"

namespace Barbarian {
 
	using namespace node;
	using namespace v8;

	static void init(Handle<Object> target) {
		HandleScope scope;
	}

	NODE_MODULE(barbarian, init);
}
