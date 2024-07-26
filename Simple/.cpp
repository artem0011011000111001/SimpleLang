#include "Struct.h"
#include "Functions.h"

using namespace Simple;

Struct::Struct(const std::string& name, std::vector<std::string> field_names, VALUE(*constructor)(Args_t))
	: name(name), field_names(field_names), constructor(constructor) {
	if (constructor) {
		Functions::RegisterDynamicFunction(name, constructor, { 2 });
	}
}