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
		String name;
		ExpressionPtr expr;
		bool IsConst;

	public:
		VariableDefineStatement(String name, ExpressionPtr expr, bool IsConst);
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
		String InitName;
		StatementPtr initialization;
		ExpressionPtr termination;
		ExpressionPtr increment;
		StatementPtr statement;

	public:
		ForStatement(String InitName, StatementPtr initialization, ExpressionPtr termination,
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
		String key;
		static Str_vec connected_modules;
		bool isPath;

	public:
		ImportStatement(String key, bool isPath = false);
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

	class SwitchStatement : public Statement {
		ExpressionPtr expr;
		SwitchBlockStatement block;

	public:
		SwitchStatement(ExpressionPtr expr, SwitchBlockStatement block);
		void execute() override;
	};

	class FunctionDefineStatement : public Statement {
		String name;
		ArgsParam_t argsParam;
		StatementPtr statement;

		std::function<VALUE(Args_t)> TurnFuncFromVoidToVALUE(StatementPtr& statement);
	public:
		FunctionDefineStatement(String name, ArgsParam_t argsParam, StatementPtr statement);

		void execute() override;

		virtual ~FunctionDefineStatement() = default;
	};

	class ConstructorDefineStatement : public Statement {
		String name;
		ArgsParam_t argsParam;
		StatementPtr statement;
		Fields_decl_t fields_params;

		std::function<VALUE(Args_t)> TurnFuncFromVoidToVALUE(StatementPtr& statement);
	public:
		ConstructorDefineStatement(String name, ArgsParam_t argsParam, StatementPtr statement, Fields_decl_t fields_params);
		void execute() override;
	};

	class ReturnStatement : public Statement {
		ExpressionPtr expr;

		friend class FunctionDefineStatement;
	public:
		ReturnStatement(ExpressionPtr expr);
		void execute() override;

		const ExpressionPtr& GetExpression() const;

		struct ReturnValue {
			ValuePtr value;
			ReturnValue(ValuePtr value);
		};
	};

	class ExpressionStatement : public Statement {
		ExpressionPtr expr;

	public:
		ExpressionStatement(ExpressionPtr expr);
		void execute() override;
	};

	class TryCatchStatement : public Statement {

		StatementPtr tryBlock;
		String key;
		bool isConst;
		String type_in_str;
		StatementPtr catchBlock;
	public:
		TryCatchStatement(StatementPtr tryBlock, const String& key, bool isConst, const String& type_in_str, StatementPtr catchBlock);
		void execute() override;
	};

	class ThrowStatement : public Statement {

		ExpressionPtr expr;
	public:
		ThrowStatement(ExpressionPtr expr);
		void execute() override;
	};
}
#endif // !_STATEMENTS_H_