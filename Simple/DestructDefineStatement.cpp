#include "AST.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

DestructDefineStatement::DestructDefineStatement(WStr_vec fields_names, WString obj_name, bool isConst)
	: fields_names(fields_names), obj_name(obj_name), isConst(isConst) {}

void DestructDefineStatement::execute() {
	
	for (size_t i = 0, size = fields_names.size(); i < size; i++) {
		WString key = fields_names[i];
		if (Variables::IsExist(key))
			throw Simple_Error("Variable already exists");

		Variables::SetNew(key, Variable(Variables::Get(obj_name)->dot(key).clone(), isConst));
	}
}