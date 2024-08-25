#include "Expressions.h"
#include "Values.h"
#include "Function.h"
#include "Functions.h"
#include "Variable.h"
#include "Variables.h"

using namespace Simple;


CallFunctionExpression::CallFunctionExpression(WString name, Vec<ExpressionPtr> args)
	: name(name), args(MOVE(args)) {}

Value& CallFunctionExpression::eval() {
	Args_t values = exprs_to_args(MOVE(args));

	if (Functions::IsExist(name))
		ref = Functions::Get(name, (int)values.size())->execute(MOVE(values));

	else if (Variables::IsExist(name))
		ref = Variables::Get(name)->operator()(MOVE(values));

	else throw Simple_Error(L"Function \"" + name + L"\" with " + std::to_wstring((int)values.size()) + L" args not defined");

	return *ref;
}

void CallFunctionExpression::AddArgument(ExpressionPtr arg) {
	args.push_back(MOVE(arg));
}