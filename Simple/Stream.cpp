#include "Stream.h"

#include <iostream>

using namespace Simple;

void Simple_libs::Stream::Stream::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Stream::Stream::InitVars() {
	_DEFINE_VAR_STR(L"endl", L"\n", true);
}

void Simple_libs::Stream::Stream::InitFuncs() {
	_DEFINE_FUNCTION(L"output", [](Args_t args) {
		size_t param_count = args.size();
		for (const auto& arg : args) {
			std::wcout << arg->AsString();
		}
		return VOID;
		}, any_args);

	_DEFINE_FUNCTION(L"outputln", [](Args_t args) {
		size_t param_count = args.size();
		for (const auto& arg : args) {
			std::wcout << arg->AsString() << std::endl;
		}
		return VOID;
		}, any_args);

	_DEFINE_FUNCTION(L"input", [](Args_t args) -> VALUE {
		size_t param_count = args.size();
		if (param_count > 1)
			throw Simple_Error("Expected 1 or 0 parameters instead of " + std::to_string(param_count));

		WString input;

		if (param_count == 0) std::wcout << L"";
		else std::wcout << args.front()->AsString();

		std::wcin >> input;

		try {
			return NUMBER(strict_stod(input));
		}
		catch (const Simple_Error&) {
			return STRING(input);
		}
		}, any_args);
}