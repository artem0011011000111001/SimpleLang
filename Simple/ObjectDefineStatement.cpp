#include "AST.h"
#include "Variables.h"
#include "Simple_defines.h"

using namespace Simple;

ObjectDefineStatement::ObjectDefineStatement(String name, Str_map<ExpressionPtr> fields, bool IsConst)
	: name(name), fields(std::move(fields)), IsConst(IsConst) {}

void ObjectDefineStatement::execute() {
	Variables::Set(name, Variable(STRUCT(name, [this]() {
		Val_map final_fields;
		for (auto& field : fields) {
			final_fields.emplace(field.first, field.second->eval().clone());
		}
		return MOVE(final_fields);
		}()), IsConst));
}