#include "TypeFunctions.h"
#include "Utils.h"
#include "Variables.h"

using namespace Simple;

ValuePtr Simple_libs::Type::Cast_number(Args_t args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return NUM_VALUE(args.front()->AsDouble());
}

ValuePtr Simple_libs::Type::Cast_string(Args_t args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return STR_VALUE(args.front()->AsString());
}

ValuePtr Simple_libs::Type::Typeof(Args_t args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return STR_VALUE(to_string(IdentifyValueType(args.front())));
}

ValuePtr Simple_libs::Type::Is_const(Args_t args) {
	size_t param_count = args.size();
	if (param_count != 1)
		throw Simple_Error("Expected 1 parameter instead of " + std::to_string(param_count));

	return NUM_VALUE(Variables::IsConstant(args.front()->AsString()));
}
