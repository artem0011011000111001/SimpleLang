#include "Math.h"

using namespace Simple;

void Math::Init() {
	InitVars();
	InitFuncs();
}

void Math::InitVars() {
	Variables::Set("PI",	CREATE_PTR<NumberValue>(MATH_PI));
	Variables::Set("E",		CREATE_PTR<NumberValue>(MATH_E));
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
