#include "Type.h"

using namespace Simple;

void Simple_libs::Type::Type::Init() {
	InitVars();
	InitFuncs();
}

void Simple_libs::Type::Type::InitVars() {

}

void Simple_libs::Type::Type::InitFuncs() {
	_DEFINE_FUNCTION_WITH_ARGS("cast_number", [](Args_t args) {
		return NUMBER(args.front()->AsDouble());
		}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("cast_string", [](Args_t args) {
		return STRING(args.front()->AsString());
		}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("typeof", [](Args_t args) {
		return STRING((args.front()->GetTypeInString()));
		}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("is_const", [](Args_t args) {
		return NUMBER(Variables::IsConstant(args.front()->AsString()));
		}, 1);
}