#include "TypeFunctions.h"
#include "Utils.h"

using namespace Simple;

ValuePtr Simple::Cast_number(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(args.front()->AsDouble());
}

ValuePtr Simple::Cast_string(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return CREATE_PTR<StringValue>(args.front()->AsString());
}

ValuePtr Simple::Typeof(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return CREATE_PTR<StringValue>(to_string(IdentifyValueType(args.front())));
}

ValuePtr Simple::Is_const(std::vector<ValuePtr> args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(Variables::IsConstant(args.front()->AsString()));
}
