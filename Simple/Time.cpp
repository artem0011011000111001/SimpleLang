#include "Time.h"

using namespace Simple;

void Time::Init() {
	InitVars();
	InitFuncs();
}

void Time::InitVars() {
	
}

void Time::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(NowFunc,   Now,   "now");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(SleepFunc, Sleep, "sleep");
}