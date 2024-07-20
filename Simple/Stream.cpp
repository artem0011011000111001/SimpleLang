#include "Stream.h"

using namespace Simple;

void Stream::Init() {
	InitVars();
	InitFuncs();
}

void Stream::InitVars() {
	_DEFINE_VAR_STR("endl", "\n", true);
}

void Stream::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(OutputFunc,	  Output,	"output");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(OutputlnFunc, Outputln, "outputln");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(InputFunc,    Input,    "input");
}