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
		virtual ValuePtr eval() const = 0;
		virtual std::string to_string() const = 0;

		virtual ~Expression() = default;
	};

	class NumberExpression : public Expression {

		const double value;
	public:

		NumberExpression(const double value);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class StringExpression : public Expression {

		const std::string value;
	public:

		StringExpression(const std::string value);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class BinaryExpression : public Expression {

		const ExpressionPtr expr1, expr2;
		const BinaryOperators operation;
	public:

		BinaryExpression(ExpressionPtr expr1, const BinaryOperators operation, ExpressionPtr expr2);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class UnaryExpression : public Expression {

		const ExpressionPtr expr;
		const std::string operation;
	public:

		UnaryExpression(const std::string operation, ExpressionPtr expr);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class VariableExpression : public Expression {

		std::string name;
	public:

		VariableExpression(const std::string& name);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class ConditionalExpression : public Expression {

		const ExpressionPtr expr1, expr2;
		const LogicOperators operation;
	public:

		ConditionalExpression(ExpressionPtr expr1, const LogicOperators operation, ExpressionPtr expr2);
		ValuePtr eval() const override;

		std::string to_string() const override;
	};

	class FunctionalExpression : public Expression {

		std::string name;
		std::vector<ExpressionPtr> args;

	public:
		FunctionalExpression(std::string name, std::vector<ExpressionPtr> args = {});
		ValuePtr eval() const override;

		void AddArgument(ExpressionPtr arg);

		std::string to_string() const override;
	};
}

#endif // !_EXPRESSIONS_H_