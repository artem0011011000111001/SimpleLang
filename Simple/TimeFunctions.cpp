#include "TimeFunctions.h"

#include <chrono>
#include <thread>

using namespace Simple;

ValuePtr Simple_libs::Time::Now(Args_t args) {
	size_t param_count = args.size();
	
	if (param_count != 0) throw Simple_Error("Expected " + std::to_string(param_count));

	//return NUM_VALUE(std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
	return NUM_VALUE(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count());
}

ValuePtr Simple_libs::Time::Sleep(Args_t args) {
	size_t param_count = args.size();
	
	if (param_count != 1) throw Simple_Error("Expected " + std::to_string(param_count));
	
	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(args.front()->AsDouble()));
	
	return ZERO;
}
