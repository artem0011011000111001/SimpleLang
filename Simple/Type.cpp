#include "Type.h"

using namespace Simple;

void Simple_libs::Type::Type::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Type::Type::InitVars() {

}

void Simple_libs::Type::Type::InitFuncs() {
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(Cast_numberFunc, Cast_number, "cast_number");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(Cast_stringFunc, Cast_string, "cast_string");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(TypeofFunc,		 Typeof,	  "typeof");
	_DEFINE_FUNCTION_AND_FUNCTION_CLASS(Is_constFunc,    Is_const,	  "is_const");
}