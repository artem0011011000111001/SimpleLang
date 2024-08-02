#include "Expressions.h"
#include "Simple_defines.h"

using namespace Simple;

ArrayExpression::ArrayExpression(Vec<ExpressionPtr> elements)
	: elements(std::move(elements)) {}

Value& Simple::ArrayExpression::eval() {
	ArrayValue arr;

	for (auto& el : elements) {
		arr.AddElement(MOVE(el->eval().clone()));
	}
	ref = ARRAY(MOVE(arr));
	return *ref;
}

