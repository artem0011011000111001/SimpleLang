#include "Type.h"

using namespace Simple;

void Type::Init() {
	InitVars();
	InitFuncs();
}

void Type::InitVars() {

}

void Type::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(Cast_numberFunc, Cast_number, "cast_number");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(Cast_stringFunc, Cast_string, "cast_string");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(TypeofFunc,		 Typeof,	  "typeof");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(IsConstFunc,     IsConst,	  "is_const");
}