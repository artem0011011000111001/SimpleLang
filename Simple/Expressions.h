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

	class StringExpression : public Expression {

		std::string value;
		ValuePtr ref;
	public:

		StringExpression(std::string value);
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
		const std::string operation;
		ValuePtr ref;
	public:

		UnaryExpression(const std::string operation, ExpressionPtr expr);
		//ValuePtr eval() override;
		Value& eval() override;
	};

	class VariableExpression : public Expression {

		std::string name;
	public:

		VariableExpression(const std::string& name);
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

		std::string name;
		std::vector<ExpressionPtr> args;
		ValuePtr ref;
	public:
		
		FunctionalExpression(std::string name, std::vector<ExpressionPtr> args = {});
		//ValuePtr eval() override;
		Value& eval() override;

		void AddArgument(ExpressionPtr arg);
	};

	class StructExpression : public Expression {

		ExpressionPtr expr;
		std::string field_name;
		ValuePtr ref;

		// for requests struct.field.field and struct.field[0]
		/*bool is_request = false;
		int index = -1;*/
	public:

		StructExpression(ExpressionPtr expr, std::string field_name);
		//ValuePtr eval() override;
		Value& eval() override;

		//void SetIndex(const int index);
	};

	class IndexExpression : public Expression {

		ExpressionPtr expr;
		ExpressionPtr pos;
		ValuePtr ref;
	public:
		IndexExpression(ExpressionPtr expr, ExpressionPtr pos);
		//ValuePtr eval() override;
		Value& eval() override;
	};
}

#endif // !_EXPRESSIONS_H_