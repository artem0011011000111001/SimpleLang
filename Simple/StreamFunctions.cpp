#include "StreamFunctions.h"
#include "Simple_defines.h"
#include "Utils.h"

#include <iostream>

using namespace Simple;

ValuePtr Simple_libs::Stream::Output(Args_t args) {
	size_t param_count = args.size();
	for (const auto& arg : args) {
		std::cout << arg->AsString();
	}
	return ZERO;
}

ValuePtr Simple_libs::Stream::Outputln(Args_t args) {
	size_t param_count = args.size();
	for (const auto& arg : args)
	{
		std::cout << arg->AsString() << std::endl;
	}
	return ZERO;
}

ValuePtr Simple_libs::Stream::Input(Args_t args) {
	size_t param_count = args.size();
	if (param_count > 1)
		throw Simple_Error("Expected 1 or 0 parameters instead of " + std::to_string(param_count));

	std::string input;

	if (param_count == 0) std::cout << "";
	else std::cout << args.front()->AsString();

	std::cin >> input;

	try
	{
		return NUM_VALUE(strict_stod(input));
	}
	catch (const Simple_Error&)
	{
		return STR_VALUE(input);
	}
}