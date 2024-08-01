#include "Structs.h"
#include "Simple_Error.h"

using namespace Simple;

bool Structs::IsExist(const String& key) {
	return structs.find(key) != structs.end();
}

Fields_decl_t Structs::Get(const String& key) {
	if (!IsExist(key))
		throw Simple_Error("Struct \"" + key + "\" not defined");
	return structs.find(key)->second;
}

void Structs::Add(const String& key, Fields_decl_t fields) {
	if (!IsExist(key))
		structs.emplace(key, fields);
}

bool Structs::_equals(const String& key1, const String& key2) {
	return key1 == key2 && Get(key1) == Get(key2);
}

Structs_t Structs::structs;