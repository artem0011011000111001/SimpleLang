#include "Field_info.h"

using namespace Simple;

BaseField_info::BaseField_info(WString type, bool isConst)
	: type(type), isConst(isConst) {}

Field_info::Field_info(WString type, bool isConst, ValuePtr defaultValue)
	: value(MOVE(defaultValue)), BaseField_info(type, isConst) {}

bool Field_info::operator==(const Field_info& other) const {
	return type == other.type && isConst == other.isConst && value == other.value;
}

Field_info Field_info::clone() const {
	return Field_info(type, isConst, value->clone());
}

RawField_info::RawField_info(WString type, bool isConst, ExpressionPtr defaultValue)
	: defaultValue(MOVE(defaultValue)), BaseField_info(type, isConst) {}