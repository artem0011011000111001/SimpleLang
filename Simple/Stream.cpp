#include "Stream.h"

using namespace Simple;

void Simple_libs::Stream::Stream::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Stream::Stream::InitVars() {
	_DEFINE_VAR_STR("endl", "\n", true);
}

void Simple_libs::Stream::Stream::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(OutputFunc,	  Output,	"output");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(OutputlnFunc, Outputln, "outputln");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(InputFunc,    Input,    "input");
}