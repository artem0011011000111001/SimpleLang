#include "MathFunctions.h"

#include <cmath>

using namespace Simple;

ValuePtr Simple::Sin(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::sin(args[0]->AsDouble()));
}

ValuePtr Simple::Cos(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::cos(args[0]->AsDouble()));
}

ValuePtr Simple::Tan(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::tan(args[0]->AsDouble()));
}

ValuePtr Simple::Sqrt(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::sqrt(args[0]->AsDouble()));
}

ValuePtr Simple::Cbrt(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::cbrt(args[0]->AsDouble()));
}

ValuePtr Simple::Round(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::round(args[0]->AsDouble()));
}

ValuePtr Simple::Floor(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::floor(args[0]->AsDouble()));
}