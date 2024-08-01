#include "Exception.h"

#include <vector>

using namespace Simple;

void Simple_libs::Exception::Exception::Init() {
	IMPORT("Type");
	InitVars();
	InitFuncs();
	InitStructs();
}

void Simple_libs::Exception::Exception::InitVars() {

}

void Simple_libs::Exception::Exception::InitFuncs() {
	_DEFINE_FUNCTION_WITH_ARGS("error", [](Args_t args) {
		throw Simple_Error(args[0]->AsString());
		return VOID;
		}, 1);
}

void Simple_libs::Exception::Exception::InitStructs() {
	Fields_decl_t type_error_fields_decl = {
		{ "error", ValueType::_STRING },
		{ "type",  ValueType::_USER_STRUCT }
	};

	Fields_decl_t value_error_fields_decl = {
		{ "error", ValueType::_STRING }
	};

	_ADD_STRUCT("TypeError", type_error_fields_decl);
	_DEFINE_STRUCT_WITH_CONSTRUCTOR("TypeError", [](Args_t args) {
		Val_map fields;

		fields.emplace("error", STRING(args[0]->AsString()));
		Args_t type_arg;
		type_arg.push_back(std::move(args[1]));

		fields.emplace("type",  Functions::Get("typeof")->execute(std::move(type_arg)));
		
		return STRUCT("TypeError", fields);
		}, 2);

	_DEFINE_STRUCT("ValueError", value_error_fields_decl);
}