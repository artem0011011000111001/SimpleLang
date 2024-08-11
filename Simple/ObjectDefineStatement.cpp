#include "AST.h"
#include "Variables.h"
#include "Simple_defines.h"

using namespace Simple;

ObjectDefineStatement::ObjectDefineStatement(WString name, WStr_map<RawVariable> fields, bool IsConst)
	: name(name), fields(MOVE(fields)), IsConst(IsConst) {}

void ObjectDefineStatement::execute() {
	Variables::Set(name, Variable(STRUCT(name, [this]() {
		Fields_t final_fields;
		for (auto& field : fields) {
			final_fields.emplace(field.first, Field(field.second.value->eval().clone(), field.second.isConst));
		}
		return MOVE(final_fields);
		}()), IsConst));
}