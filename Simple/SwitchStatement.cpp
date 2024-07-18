#include "AST.h"
#include "Simple_Error.h"

using namespace Simple;

SwitchStatement::SwitchStatement(ExpressionPtr expr, SwitchBlockStatement block)
	: expr(std::move(expr)), block(std::move(block)) {}

void SwitchStatement::execute() {
	ValuePtr ExprRes = expr->eval();    

	for (auto& Case : block.getCaseStatements()) {

        if (Case.IsDefault()) {
            try {
                Case.execute();
            }
            catch (const BreakStatement&) {
                break;
            }
        }
        else if (ExprRes->operator==(Case.GetExpression()->eval())) {
            try {
                Case.execute();
            }
            catch (const BreakStatement&) {
                break;
            }
        }
	}
}

std::string SwitchStatement::to_string() {
	return "switch (" + expr->to_string() + ") {\n" + block.to_string() + "}";
}