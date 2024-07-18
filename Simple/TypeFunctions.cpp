#include "TypeFunctions.h"
#include "Utils.h"

using namespace Simple;

ValuePtr Simple::Cast_number(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return std::make_unique<NumberValue>(args.front()->AsDouble());
}

ValuePtr Simple::Cast_string(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return std::make_unique<StringValue>(args.front()->AsString());
}

ValuePtr Simple::Typeof(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return std::make_unique<StringValue>(to_string(IdentifyValueType(args.front())));
}

ValuePtr Simple::IsConst(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return std::make_unique<NumberValue>(Variables::IsConstant(args.front()->AsString()));
}
