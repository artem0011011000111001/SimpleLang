#pragma once

#ifndef _STATEMENTS_H_
#define _STATEMENTS_H_

#include "Simple_typedefs.h"
#include "Expressions.h"
#include "Values.h"

#include <list>
#include <string>
#include <unordered_map>
#include <functional>

namespace Simple {

	class Statement {
	public:
		virtual void execute() = 0;
		virtual ~Statement() = default;

		virtual std::string to_string() = 0;
	};

	class AssigmentStatement : public Statement {
		std::string variable;
		ExpressionPtr expression;

	public:
		AssigmentStatement(std::string variable, ExpressionPtr expression);
		void execute() override;

		std::string to_string() override;
	};

	class ConstAssigmentStatement : public Statement {
		std::string variable;
		ExpressionPtr expression;

	public:
		ConstAssigmentStatement(std::string variable, ExpressionPtr expression);
		void execute() override;

		std::string to_string() override;
	};

	class PrintStatement : public Statement {
		ExpressionPtr expr;

	public:
		PrintStatement(ExpressionPtr expr);
		void execute() override;

		std::string to_string() override;
	};

	class IfStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr ifStatement, elseStatement;

	public:
		IfStatement(ExpressionPtr expr, StatementPtr ifStatement, StatementPtr elseStatement);
		void execute() override;

		std::string to_string() override;
	};

	class GlobalBlockStatement : public Statement {
		std::list<StatementPtr> statements;

	public:
		GlobalBlockStatement() = default;
		virtual void execute() override;

		void add(StatementPtr statement);

		std::string to_string() override;
	};

	class BlockStatement : public Statement {
		std::list<StatementPtr> statements;

	public:
		BlockStatement() = default;
		void execute() override;

		void add(StatementPtr statement);

		std::string to_string() override;
	};

	class ShortBlockStatement : public Statement {
		StatementPtr statement;

	public:
		ShortBlockStatement(StatementPtr statement);
		void execute() override;

		std::string to_string() override;
	};

	class DoWhileStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr statement;

	public:
		DoWhileStatement(ExpressionPtr condition, StatementPtr statement);
		void execute() override;

		std::string to_string() override;
	};

	class WhileStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr statement;

	public:
		WhileStatement(ExpressionPtr condition, StatementPtr statement);
		void execute() override;

		std::string to_string() override;
	};

	class ForStatement : public Statement {
		std::string InitName;
		StatementPtr initialization;
		ExpressionPtr termination;
		StatementPtr increment;
		StatementPtr statement;

	public:
		ForStatement(std::string InitName, StatementPtr initialization, ExpressionPtr termination,
			StatementPtr increment, StatementPtr block);
		void execute() override;

		std::string to_string() override;
	};

	class BreakStatement : public Statement {
		void execute() override;
		std::string to_string() override;
	};

	class ContinueStatement : public Statement {
		void execute() override;
		std::string to_string() override;
	};

	class FunctionStatement : public Statement {
		FunctionalExpression function;

	public:
		FunctionStatement(FunctionalExpression function);
		void execute() override;

		std::string to_string() override;
	};

	class ImportStatement : public Statement {
		std::string module_name;

	public:
		ImportStatement(std::string module_name);
		void execute() override;

		std::string to_string() override;
	};

	class CaseStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr statement;
		bool isDefault;

	public:
		CaseStatement(ExpressionPtr expr, StatementPtr statement, bool isDefault = false);
		void execute() override;

		ExpressionPtr GetExpression();

		bool IsDefault() const {
			return isDefault;
		}

		std::string to_string() override;
	};

	class SwitchBlockStatement : public Statement {
		std::list<CaseStatement> CaseStatements;

	public:
		SwitchBlockStatement() = default;
		void execute() override;

		void add(CaseStatement statement);

		// CaseStatement Get(size_t pos);

		std::list<CaseStatement>& getCaseStatements();

		std::string to_string() override;
	};

	class SwitchStatement : public Statement {
		ExpressionPtr expr;
		SwitchBlockStatement block;

	public:
		SwitchStatement(ExpressionPtr expr, SwitchBlockStatement block);
		void execute() override;

		std::string to_string() override;
	};

	class FunctionDefineStatement : public Statement {
		std::string name;
		std::list<std::string> argsNames;
		StatementPtr statement;

		std::function <ValuePtr(std::vector<ValuePtr>)> TurnFuncFromVoidToValuePtr(StatementPtr& statement);

	public:
		FunctionDefineStatement(std::string name, std::list<std::string> argsNames, StatementPtr statement);

		void execute() override;

		std::string to_string() override;
	};

	class ReturnStatement : public Statement {
		ExpressionPtr expr;

	public:
		ReturnStatement(ExpressionPtr expr);
		void execute() override;

		const ExpressionPtr& GetExpression() const;

		std::string to_string() override;

	};
}
#endif // !_STATEMENTS_H_