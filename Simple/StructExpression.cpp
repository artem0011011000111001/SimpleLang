#include "Expressions.h"
#include "Variables.h"
#include "Simple_Error.h"

#include <iostream>

using namespace Simple;

StructExpression::StructExpression(ExpressionPtr expr, std::string field_name)
	: expr(std::move(expr)), field_name(field_name) {}

//ValuePtr StructExpression::eval() {
//	if (is_request)
//		return expr->eval()->dot(field_name)->operator[](index);
//	return expr->eval()->dot(field_name);
//}

Value& StructExpression::eval() {
   return expr->eval().dot(field_name);
}

//StructExpression::~StructExpression() {
//    std::cout << "destructor";
//    if (ref) {
//        delete ref;
//        ref = nullptr;
//    }
//}

//void StructExpression::SetIndex(const int index) {
//	this->index = index;
//	is_request = true;
//}