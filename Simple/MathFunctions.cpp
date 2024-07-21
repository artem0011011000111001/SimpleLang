#include "MathFunctions.h"

#include <cmath>

using namespace Simple;

VALUE Simple_libs::Math::Sin(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::sin(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Cos(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::cos(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Tan(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::tan(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Sqrt(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::sqrt(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Cbrt(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::cbrt(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Round(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::round(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Floor(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::floor(args[0]->AsDouble()));
}

VALUE Simple_libs::Math::Log(Args_t args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	return NUM_VALUE(std::log(args[0]->AsDouble()));
}
