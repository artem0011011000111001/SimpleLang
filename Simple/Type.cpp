#include "Type.h"
#include "Utils.h"

using namespace Simple;

void Simple_libs::Type::Type::Init() {
	InitVars();
	InitFuncs();
	InitStruct();
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

	_DEFINE_FUNCTION_WITH_ARGS("is_const", [](Args_t args) {
		return NUMBER(Variables::IsConstant(args.front()->AsString()));
		}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("instanseof", [](Args_t args) -> VALUE {
		return BOOL(equals_type(CALL("typeof", HAND_OVER_ARGS({ MOVE(args[0]) }) )->dot("name").AsString(), CALL("typeof", HAND_OVER_ARGS({ MOVE(args[1]) }))->dot("name").AsString()));
		}, 2);
}

void Simple_libs::Type::Type::InitStruct() {

	Fields_decl_t type_of_fields_decl = {
			{ "name",		  ValueType::_STRING },
			{ "category",     ValueType::_STRING },
			{ "fields_count", ValueType::_NUMBER}
	};

	_ADD_STRUCT("typeof", type_of_fields_decl);
	
	_DEFINE_STRUCT_WITH_CONSTRUCTOR("typeof", [](Args_t args) {
		Val_map fields;

		fields.emplace("name", STRING(args[0]->GetTypeInString()));
		fields.emplace("category", STRING(IdentifyCategory(args[0]->GetType())));
		fields.emplace("fields_count", NUMBER(args[0]->GetType() == ValueType::_STRUCT ?
			dynamic_cast<StructValue*>(args[0].get())->fields_count() : 0));

		return STRUCT("typeof", fields);
		}, 1);

	Fields_decl_t is_exist_fields_decl = {
			{ "_var",    ValueType::_NUMBER },
			{ "_func",   ValueType::_NUMBER },
			{ "_struct", ValueType::_NUMBER}
	};

	_ADD_STRUCT("is_exist", is_exist_fields_decl);

	_DEFINE_STRUCT_WITH_CONSTRUCTOR("is_exist", [](Args_t args) {
		Val_map fields;

		CHECK_TYPE("str", args[0]);

		std::string key = args[0]->AsString();

		fields.emplace("_var", BOOL(Variables::IsExist(key)));
		fields.emplace("_func", BOOL(Functions::IsExist(key)));
		fields.emplace("_struct", BOOL(Structs::IsExist(key)));

		return STRUCT("is_exist", fields);
		}, 1);
}