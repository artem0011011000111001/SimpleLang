#include "Stream.h"

#include <iostream>

using namespace Simple;

void Simple_libs::Stream::Stream::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Stream::Stream::InitVars() {
	_DEFINE_VAR_STR("endl", "\n", true);
}

void Simple_libs::Stream::Stream::InitFuncs() {
	_DEFINE_FUNCTION("output", [](Args_t args) {
		size_t param_count = args.size();
		for (const auto& arg : args) {
			std::cout << arg->AsString();
		}
		return VOID;
		});
	_DEFINE_FUNCTION("outputln", [](Args_t args) {
		size_t param_count = args.size();
		for (const auto& arg : args) {
			std::cout << arg->AsString() << std::endl;
		}
		return VOID;
		});
	_DEFINE_FUNCTION("input", [](Args_t args) -> VALUE {
		size_t param_count = args.size();
		if (param_count > 1)
			throw Simple_Error("Expected 1 or 0 parameters instead of " + std::to_string(param_count));

		String input;

		if (param_count == 0) std::cout << "";
		else std::cout << args.front()->AsString();

		std::cin >> input;

		try {
			return NUMBER(strict_stod(input));
		}
		catch (const Simple_Error&) {
			return STRING(input);
		}
		});
}