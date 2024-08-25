#pragma once

#ifndef _FIELD_INFO_H_
#define _FIELD_INFO_H_

#include "Utils.h"
#include "Expressions.h"
#include "Simple_defines.h"

namespace Simple {

	struct BaseField_info {
		WString type;
		bool isConst = false;

		BaseField_info(WString type, bool isConst = false);
		BaseField_info() = default;

		virtual ~BaseField_info() = default;
	};

	struct Field_info : BaseField_info {
		ValuePtr value;

		Field_info(WString type, bool isConst = false, ValuePtr value = NOT_VALUE);
		Field_info() = default;

		bool operator==(const Field_info& other) const;

		Field_info clone() const;
	};

	struct RawField_info : BaseField_info {
		ExpressionPtr defaultValue;

		RawField_info(WString type, bool isConst = false, ExpressionPtr defaultValue = EXPR_NOT_VALUE);
	};
}

#endif // _FIELD_INFO_H_