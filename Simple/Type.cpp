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

	_DEFINE_FUNCTION(L"is_const", [](Args_t args) {
		return NUMBER(Variables::IsConstant(args.front()->AsString()));
		}, 1);

	_DEFINE_FUNCTION(L"instanseof", [](Args_t args) -> VALUE {
		return BOOL(equals_type(args[0]->GetTypeInString(), args[1]->GetTypeInString()));
		}, 2);
}

void Simple_libs::Type::Type::InitStruct() {
	
	DEF_STRUCT(typeof)

	FIELD(L"name",		   L"str", false, NOT_VALUE);
	FIELD(L"category",     L"str", false, NOT_VALUE);
	FIELD(L"fields_count", L"str", false, NOT_VALUE);
	FIELD(L"fields_names", L"str", false, NOT_VALUE);

	CONSTRUCTOR({

		StructValue* struct_value;
		if (struct_value = dynamic_cast<StructValue*>(args[0].get()));
		else struct_value = nullptr;
		
		fields[L"name"].value		  =	STRING(args[0]->GetTypeInString());
		fields[L"category"].value	  =	STRING(IdentifyCategory(args[0]->GetType()));
		fields[L"fields_count"].value = NUMBER(struct_value ?
			struct_value->fields_count() : 0);

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
		fields[L"fields_names"].value = ARRAY(MOVE(fields_names));

	}, 1);

		END_STRUCT(typeof);


	DEF_STRUCT(is_exist)

	FIELD(L"_var_",    L"num", false, NOT_VALUE);
	FIELD(L"_func_",   L"num", false, NOT_VALUE);
	FIELD(L"_struct_", L"num", false, NOT_VALUE);

	CONSTRUCTOR({

		CHECK_TYPE(L"str", args[0]);

		WString key = args[0]->AsString();

		fields[L"_var_"].value    = BOOL(Variables::IsExist(key));
		fields[L"_func_"].value   = BOOL(Functions::IsExist(key));
		fields[L"_struct_"].value = BOOL(Structs::IsExist(key));

		}, 1);

		END_STRUCT(is_exist);

	/*static Fields_decl_t typeofFields = DECL_FIELDS({
		{ L"name",         FIELD_INFO(L"str") },
		{ L"category",     FIELD_INFO(L"str") },
		{ L"fields_count", FIELD_INFO(L"num") },
		{ L"fields_names", FIELD_INFO(L"arr") }
		});

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
	}, 1, typeofFields);*/
	/*static Fields_decl_t is_existFields = DECL_FIELDS({
		{ L"_var_",    FIELD_INFO(L"num") },
		{ L"_func_",   FIELD_INFO(L"num") },
		{ L"_struct_", FIELD_INFO(L"num") }
		});

	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"is_exist", BLOCK(args) {
		Fields_t fields;

		CHECK_TYPE(L"str", args[0]);

		WString key	  = args[0]->AsString();

		fields.emplace(L"_var_",    BOOL(Variables::IsExist(key)));
		fields.emplace(L"_func_",   BOOL(Functions::IsExist(key)));
		fields.emplace(L"_struct_", BOOL(Structs::IsExist(key)));

		return STRUCT(L"is_exist", fields);
	}, 1, is_existFields);*/
}