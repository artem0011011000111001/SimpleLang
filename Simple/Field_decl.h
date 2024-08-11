#pragma once

#ifndef _FIELD_DECL_H_
#define _FIELD_DECL_H_

#include "Utils.h"
#include "Expressions.h"
#include "Simple_defines.h"

namespace Simple {

	struct BaseField_decl {
		WString type;
		bool isConst;

		BaseField_decl(WString type, bool isConst = false);
	};

	struct Field_decl : BaseField_decl {
		ValuePtr defaultValue;

		Field_decl(WString type, bool isConst = false, ValuePtr defaultValue = NOT_VALUE);

		bool operator==(const Field_decl& other) const;
	};

	struct RawField_decl : BaseField_decl {
		ExpressionPtr defaultValue;

		RawField_decl(WString type, bool isConst = false, ExpressionPtr defaultValue = NOT_VALUE);
	};
}

#endif // _FIELD_DECL_H_