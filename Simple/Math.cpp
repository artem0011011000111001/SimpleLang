#include "Math.h"

using namespace Simple;

void Math::Init() {
	InitVars();
	InitFuncs();
}

void Math::InitVars() {
	_DEFINE_VAR_NUM("PI", MATH_PI, true);
	_DEFINE_VAR_NUM("E",  MATH_E,  true);
}

void Math::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(SinFunc,   Sin,   "sin");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(CosFunc,   Cos,   "cos");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(TanFunc,   Tan,   "tan");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(SqrtFunc,  Sqrt,  "sqrt");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(CbrtFunc,  Cbrt,  "cbrt");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(RountFunc, Round, "round");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(FloorFunc, Floor, "floor");
}
