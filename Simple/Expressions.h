#pragma once

#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_

#include "Simple_typedefs.h"
#include "Utils.h"

#include <string>
#include <vector>

namespace Simple {

	class Expression {
	public:
		//virtual ValuePtr eval() = 0;
		virtual Value& eval() = 0;

		virtual ~Expression() = default;
	};

	class NumberExpression : public Expression {

		double value;
		ValuePtr ref;
	public:

		NumberExpression(double value);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class DigitExpression : public Expression {

		double value;
		ValuePtr ref;
	public:
		DigitExpression(double value);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class StringExpression : public Expression {

		String value;
		ValuePtr ref;
	public:

		StringExpression(String value);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class CharExpression : public Expression {

		String value;
		ValuePtr ref;
	public:

		CharExpression(String value);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class BinaryExpression : public Expression {

		const ExpressionPtr expr1, expr2;
		const BinaryOperators operation;
		ValuePtr ref;
	public:

		BinaryExpression(ExpressionPtr expr1, const BinaryOperators operation, ExpressionPtr expr2);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class UnaryExpression : public Expression {

		const ExpressionPtr expr;
		const UnaryOperators operation;
		ValuePtr ref;
	public:

		UnaryExpression(const UnaryOperators operation, ExpressionPtr expr);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class VariableExpression : public Expression {

		String name;
	public:

		VariableExpression(const String& name);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class ConditionalExpression : public Expression {

		const ExpressionPtr expr1, expr2;
		const LogicOperators operation;
		ValuePtr ref;
	public:

		ConditionalExpression(ExpressionPtr expr1, const LogicOperators operation, ExpressionPtr expr2);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class FunctionalExpression : public Expression {

		String name;
		std::vector<ExpressionPtr> args;
		ValuePtr ref;
	public:
		
		FunctionalExpression(String name, std::vector<ExpressionPtr> args = {});
		//ValuePtr eval() override;
		Value& eval() override;

		void AddArgument(ExpressionPtr arg);
	};

	class StructExpression : public Expression {

		ExpressionPtr expr;
		String field_name;
	public:

		StructExpression(ExpressionPtr expr, String field_name);

		Value& eval() override;
	};

	class VoidExpression : public Expression {

		ValuePtr ref;
	public:

		VoidExpression() = default;

		Value& eval() override;
	};

	class IndexExpression : public Expression {

		ExpressionPtr expr;
		ExpressionPtr pos;
	public:
		IndexExpression(ExpressionPtr expr, ExpressionPtr pos);

		Value& eval() override;
	};
}

#endif // !_EXPRESSIONS_H_