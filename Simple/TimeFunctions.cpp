#include "TimeFunctions.h"

#include <chrono>
#include <thread>

using namespace Simple;

ValuePtr Simple::Now(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 0) throw Simple_Error("Expected " + std::to_string(param_count));

	return CREATE_PTR<NumberValue>(std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

ValuePtr Simple::Sleep(std::vector<ValuePtr> args) {
	size_t param_count = args.size();

	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));

	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(args.front()->AsDouble()));

	return ZERO;
}
