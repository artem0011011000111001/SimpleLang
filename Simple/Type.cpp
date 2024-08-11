#include "Type.h"
#include "Utils.h"

#include <algorithm>

using namespace Simple;

void Simple_libs::Type::Type::Init() {
	InitVars();
	InitFuncs();
	InitStruct();
}

void Simple_libs::Type::Type::InitVars() {

}

void Simple_libs::Type::Type::InitFuncs() {
	_DEFINE_FUNCTION(L"cast_number", [](Args_t args) {
		return NUMBER(args.front()->AsDouble());
		}, 1);

	_DEFINE_FUNCTION(L"cast_string", [](Args_t args) {
		return STRING(args.front()->AsString());
		}, 1);

	_DEFINE_FUNCTION(L"is_const", [](Args_t args) {
		return NUMBER(Variables::IsConstant(args.front()->AsString()));
		}, 1);

	_DEFINE_FUNCTION(L"instanseof", [](Args_t args) -> VALUE {
		return BOOL(equals_type(args[0]->GetTypeInString(), args[1]->GetTypeInString()));
		}, 2);
}

void Simple_libs::Type::Type::InitStruct() {
	
	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"typeof", BLOCK(args) {
		Fields_t fields;

		StructValue* struct_value;
		if (struct_value = dynamic_cast<StructValue*>(args[0].get()));
		else struct_value = nullptr;

		fields.emplace(L"name",			STRING(args[0]->GetTypeInString()));
		fields.emplace(L"category",		STRING(IdentifyCategory(args[0]->GetType())));
		fields.emplace(L"fields_count", NUMBER(struct_value ?
			struct_value->fields_count() : 0));

		Elements_t fields_names;
		if (struct_value) {
			WStr_vec str_fields_names = struct_value->fields_names();
			fields_names.resize(str_fields_names.size());

			std::transform(str_fields_names.begin(), str_fields_names.end(),
				fields_names.begin(), [](const WString& val) {
					return STRING(val);
				}
			);
		}
		fields.emplace(L"fields_names", ARRAY(MOVE(fields_names)));

		return STRUCT(L"typeof", fields);
		}, 1, FIELD_DECL(
			fields.emplace(L"name",			L"str"),
			fields.emplace(L"category",		L"str"),
			fields.emplace(L"fields_count", L"str")
		));

	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"is_exist", BLOCK(args) {
		Fields_t fields;

		CHECK_TYPE(L"str", args[0]);

		WString key	  = args[0]->AsString();

		fields.emplace(L"_var",    BOOL(Variables::IsExist(key)));
		fields.emplace(L"_func",   BOOL(Functions::IsExist(key)));
		fields.emplace(L"_struct", BOOL(Structs::IsExist(key)));

		return STRUCT(L"is_exist", fields);
		}, 1, FIELD_DECL(
			fields.emplace(L"_var", L"num"),
			fields.emplace(L"_var", L"num"),
			fields.emplace(L"_var", L"num")
		));
}