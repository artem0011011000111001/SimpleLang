#include "Expressions.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variables.h"
#include "Functions.h"

using namespace Simple;

WordExpression::WordExpression(const WString& name) : name(name) {}

//ValuePtr VariableExpression::eval() {
//	return get_ref().clone();
//}

Value& WordExpression::eval() {
	if (Variables::IsExist(name))
		return Variables::GetRef(name);

	else if (Functions::IsExist(name)) {
		ref = FUNCTION(name);
		return *ref;
	}

	else throw Simple_Error(L"\"" + name + L"\" not defined");
}