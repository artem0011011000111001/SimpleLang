#include "Time.h"

using namespace Simple;

void Simple_libs::Time::Time::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Time::Time::InitVars() {

}

void Simple_libs::Time::Time::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(NowFunc,   Now,   "now");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(SleepFunc, Sleep, "sleep");
}