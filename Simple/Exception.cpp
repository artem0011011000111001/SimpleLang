#include "Exception.h"

#include <vector>

using namespace Simple;

void Simple_libs::Exception::Exception::Init() {
	IMPORT(L"Type");
	InitVars();
	InitFuncs();
	InitStructs();
}

void Simple_libs::Exception::Exception::InitVars() {

}

void Simple_libs::Exception::Exception::InitFuncs() {
	_DEFINE_FUNCTION(L"error", [](Args_t args) {
		throw Simple_Error(args[0]->AsString());
		return VOID;
		}, 1);
}

void Simple_libs::Exception::Exception::InitStructs() {

	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"TypeError", BLOCK(args) {
		Fields_t fields;

		fields.emplace(L"error", Field(STRING(args[0]->AsString()), true));		
		fields.emplace(L"type",  CALL(L"typeof", HAND_OVER_ARGS(MOVE(args[1]))));

		return STRUCT(L"TypeError", fields);
	}, 2, FIELD_DECL(fields.emplace(L"error", L"str")));

	_DEFINE_STRUCT(L"ValueError", FIELD_DECL(fields.emplace(L"error", L"str")));
}