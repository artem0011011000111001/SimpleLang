#include "Time.h"

#include <chrono>
#include <thread>

using namespace Simple;

void Simple_libs::Time::Time::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Time::Time::InitVars() {

}

void Simple_libs::Time::Time::InitFuncs() {
	_DEFINE_FUNCTION_WITH_ARGS_S(now, [](Args_t args) {
		return NUMBER(std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count());
		}, 0);

	_DEFINE_FUNCTION_WITH_ARGS_S(sleep, [](Args_t args) {
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(args.front()->AsDouble()));
		return ZERO;
	}, 1);
}