#pragma once

#ifndef _STATEMENTS_H_
#define _STATEMENTS_H_

#include "Simple_typedefs.h"
#include "Expressions.h"
#include "Values.h"
#include "Simple_typedefs.h"

#include <list>
#include <string>
#include <unordered_map>
#include <functional>

namespace Simple {

	class Statement {
	public:
		virtual void execute() = 0;
		virtual ~Statement() = default;
	};

	class VariableDefineStatement : public Statement {
		std::string name;
		ExpressionPtr expr;
		bool IsConst;

	public:
		VariableDefineStatement(std::string name, ExpressionPtr expr, bool IsConst);
		void execute() override;
	};

	class AssigmentStatement : public Statement {
		ExpressionPtr expr1;
		ExpressionPtr expr2;

	public:
		AssigmentStatement(ExpressionPtr expr1, ExpressionPtr expr2);
		void execute() override;
	};

	class AbbreviatedOperationsStatement : public Statement {
		ExpressionPtr expr1;
		ExpressionPtr expr2;
		BinaryOperators operation;

	public:
		AbbreviatedOperationsStatement(ExpressionPtr expr1, BinaryOperators operation, ExpressionPtr expr2);
		void execute() override;
	};

	class IfStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr ifStatement, elseStatement;

	public:
		IfStatement(ExpressionPtr expr, StatementPtr ifStatement, StatementPtr elseStatement);
		void execute() override;
	};

	class GlobalBlockStatement : public Statement {
		std::list<StatementPtr> statements;

	public:
		GlobalBlockStatement() = default;
		virtual void execute() override;

		void add(StatementPtr statement);
	};

	class BlockStatement : public Statement {
		std::list<StatementPtr> statements;

	public:
		BlockStatement() = default;
		void execute() override;

		void add(StatementPtr statement);
	};

	class ShortBlockStatement : public Statement {
		StatementPtr statement;

	public:
		ShortBlockStatement(StatementPtr statement);
		void execute() override;
	};

	class DoWhileStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr statement;

	public:
		DoWhileStatement(ExpressionPtr condition, StatementPtr statement);
		void execute() override;
	};

	class WhileStatement : public Statement {
		ExpressionPtr expr;
		StatementPtr statement;

	public:
		WhileStatement(ExpressionPtr condition, StatementPtr statement);
		void execute() override;
	};

	class ForStatement : public Statement {
		std::string InitName;
		StatementPtr initialization;
		ExpressionPtr termination;
		ExpressionPtr increment;
		StatementPtr statement;

	public:
		ForStatement(std::string InitName, StatementPtr initialization, ExpressionPtr termination,
			ExpressionPtr increment, StatementPtr block);
		void execute() override;
	};

	class BreakStatement : public Statement {
	public:
		void execute() override;
	};

	class ContinueStatement : public Statement {
	public:
		void execute() override;
	};

	class ImportStatement : public Statement {
		std::string module_name;

	public:
		ImportStatement(std::string module_name);
		void execute() override;
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
	};

	class SwitchBlockStatement : public Statement {
		std::list<CaseStatement> CaseStatements;

	public:
		SwitchBlockStatement() = default;
		void execute() override;

		void add(CaseStatement statement);

		// CaseStatement Get(size_t pos);

		std::list<CaseStatement>& getCaseStatements();
	};

	/*class StructBlockStatement : public Statement {
		std::vector<std::string> fields_names;
		VALUE(*constructor)(Args_t) = nullptr;

	public:
		StructBlockStatement() = default;
		void execute() override;

		void add(CaseStatement statement);

		void setConstructor(VALUE(*constructor)(Args_t));

		std::string to_string() override;
	};*/

	class SwitchStatement : public Statement {
		ExpressionPtr expr;
		SwitchBlockStatement block;

	public:
		SwitchStatement(ExpressionPtr expr, SwitchBlockStatement block);
		void execute() override;
	};

	class FunctionDefineStatement : public Statement {
		std::string name;
		std::pair<std::list<std::string>, std::list<bool>> argsParam;
		StatementPtr statement;

		std::function <ValuePtr(std::vector<ValuePtr>)> TurnFuncFromVoidToValuePtr(StatementPtr& statement);

	public:
		FunctionDefineStatement(std::string name, std::pair<std::list<std::string>, std::list<bool>>, StatementPtr statement);

		void execute() override;
	};

	class ReturnStatement : public Statement {
		ExpressionPtr expr;

	public:
		ReturnStatement(ExpressionPtr expr);
		void execute() override;

		const ExpressionPtr& GetExpression() const;
	};

	class ExpressionStatement : public Statement {
		ExpressionPtr expr;

	public:
		ExpressionStatement(ExpressionPtr expr);
		void execute() override;
	};
}
#endif // !_STATEMENTS_H_