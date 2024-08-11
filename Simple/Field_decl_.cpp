#include "Field_decl.h"

using namespace Simple;

BaseField_decl::BaseField_decl(WString type, bool isConst)
	: type(type), isConst(isConst) {}

Field_decl::Field_decl(WString type, bool isConst, ValuePtr defaultValue)
	: defaultValue(MOVE(defaultValue)), BaseField_decl(type, isConst) {}

bool Field_decl::operator==(const Field_decl& other) const {
	return type == other.type && isConst == other.isConst && defaultValue == other.defaultValue;
}

RawField_decl::RawField_decl(WString type, bool isConst, ExpressionPtr defaultValue)
	: defaultValue(MOVE(defaultValue)), BaseField_decl(type, isConst) {}