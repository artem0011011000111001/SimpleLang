#pragma once

#ifndef _STATEMENTS_H_
#define _STATEMENTS_H_

#include "Simple_typedefs.h"
#include "Expressions.h"
#include "Values.h"
#include "Simple_defines.h"
#include "RawVariable.h"

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
		WString name;
		ExpressionPtr expr;
		bool IsConst;

	public:
		VariableDefineStatement(WString name, ExpressionPtr expr, bool IsConst);
		void execute() override;
	};

	class ObjectDefineStatement : public Statement {
		WString name;
		WStr_map<RawVariable> fields;
		bool IsConst;

	public:
		ObjectDefineStatement(WString name, WStr_map<RawVariable> fields, bool IsConst);
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
		WString InitName;
		StatementPtr initialization;
		ExpressionPtr termination;
		ExpressionPtr increment;
		StatementPtr statement;

	public:
		ForStatement(WString InitName, StatementPtr initialization, ExpressionPtr termination,
			ExpressionPtr increment, StatementPtr block);
		void execute() override;
	};

	class ForEachStatement : public Statement {
		WString name;
		bool isConst;
		WString in;
		StatementPtr block;

	public:
		ForEachStatement(WString name, bool isConst, WString in, StatementPtr block);
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
		WString key;
		static WStr_vec connected_modules;
		bool isPath;

	public:
		ImportStatement(WString key, bool isPath = false);
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
		WString name;
		ArgsParams_t argsParam;
		StatementPtr statement;
		bool is_any_args;

		std::function<VALUE(Args_t)> TurnFuncFromVoidToVALUE(StatementPtr& statement);
	public:
		FunctionDefineStatement(WString name, ArgsParams_t argsParam, StatementPtr statement, bool is_any_args);

		void execute() override;

		virtual ~FunctionDefineStatement() = default;
	};

	class StructDefineStatement : public Statement {

		WString name;
		Vec<ArgsParams_t> argsParam;
		Vec<StatementPtr> statements;
		Vec<bool> is_any_args;

		Fields_decl_t fields_params;
		RawFields_decl_t RawFields_params;

		std::function<VALUE(Args_t)> TurnFuncFromVoidToVALUE(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args_);
	public:
		StructDefineStatement(WString name, Vec<ArgsParams_t> argsParam, Vec<StatementPtr> statements, RawFields_decl_t RawFields_params, Vec<bool> is_any_args);
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

		WStr_vec keys;
		Vec<bool> isConsts;
		WStr_vec types_in_str;
		Vec<StatementPtr> catchBlocks;
		StatementPtr finally_block;
	public:
		TryCatchStatement(StatementPtr tryBlock, const WStr_vec& keys, Vec<bool> isConsts, const WStr_vec& types_in_str, Vec<StatementPtr> catchBlocks, StatementPtr finally_block);
		void execute() override;	
	};

	class ThrowStatement : public Statement {

		ExpressionPtr expr;
	public:
		ThrowStatement(ExpressionPtr expr);
		void execute() override;
	};

	class DestructDefineStatement : public Statement {

		WStr_vec fields_names;
		WString obj_name;
		bool isConst;
	public:
		DestructDefineStatement(WStr_vec fields_names, WString obj_name, bool isConst);
		void execute() override;
	};

	class ClassDefineStatement : public Statement {

		WString name;
		RawClassFields_decl_t fields_params;
		ClassFields_decl_t fields;
		RawMethod_decl_t methods_params;
	public:
		ClassDefineStatement(const WString& name, RawClassFields_decl_t fields_params, RawMethod_decl_t methods_params);
		void execute() override;
	};
}
#endif // !_STATEMENTS_H_