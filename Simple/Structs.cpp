#include "Structs.h"
#include "Field_info.h"
#include "Simple_Error.h"

using namespace Simple;

bool Structs::IsExist(const WString& key) {
	return structs.find(key) != structs.end();
}

Fields_decl_t Structs::Get(const WString& key) {
	if (!IsExist(key))
		throw Simple_Error(L"Struct \"" + key + L"\" not defined");
	return copy_fields_params(structs.find(key)->second);
}

void Structs::Add(const WString& key, Fields_decl_t fields) {
	if (!IsExist(key))
		structs.emplace(key, MOVE(fields));
}

bool Structs::_equals(const WString& key1, const WString& key2) {
	return key1 == key2 && Get(key1) == Get(key2);
}

Structs_t Structs::structs;