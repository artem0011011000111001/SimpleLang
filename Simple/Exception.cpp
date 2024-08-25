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

	_DEFINE_FUNCTION(L"call", [](Args_t args) {
		return CALL(args[0]->AsString(), HAND_OVER_ARGS({}));
		}, 1);
}

void Simple_libs::Exception::Exception::InitStructs() {

	DEF_STRUCT(TypeError)

	FIELD(L"error", L"str",    false, NOT_VALUE);
	FIELD(L"type",  L"typeof", false, NOT_VALUE);

	CONSTRUCTOR({

		Args_t args_ = _HAND_OVER_ARGS(MOVE(args[1]));

		fields[L"error"].value = STRING(args[0]->AsString());
		fields[L"type"].value  = CALL(L"typeof", MOVE(args_));

		}, 2)

		END_STRUCT(TypeError);

	/*static Fields_decl_t TypeErrorFields = DECL_FIELDS({
		{ L"error",	 FIELD_INFO(L"str") },
		{ L"type",   FIELD_INFO(L"typeof", true) }
	});

	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"TypeError", BLOCK(args) {
		Fields_t fields;

		fields.emplace(L"error", Field(STRING(args[0]->AsString())));
		fields.emplace(L"type",  CALL(L"typeof", HAND_OVER_ARGS(MOVE(args[1]))));

		return STRUCT(L"TypeError", fields);
	}, 2, TypeErrorFields);*/


	DEF_STRUCT(ValueError)

	FIELD(L"error", L"str", false, NOT_VALUE);

	CONSTRUCTOR({

		fields[L"error"].value = STRING(args[0]->AsString());

		}, 1)

		END_STRUCT(ValueError);

	/*static Fields_decl_t ValueErrorFields = DECL_FIELDS({
		{ L"error",	 FIELD_INFO(L"str") },
	});

	_DEFINE_STRUCT(L"ValueError", ValueErrorFields);*/
}