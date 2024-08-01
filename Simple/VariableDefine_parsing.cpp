#include "Parser.h"
#include "Simple_Error.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::VariableDefine(bool isConst) {

	std::string name = consume(TokenType::WORD).getText();

	consume(TokenType::EQ);

	ExpressionPtr expr = expression();

	return CREATE_PTR<VariableDefineStatement>(name, std::move(expr), isConst);
}

StatementPtr Parser::ConstVariableDefine() {
	return VariableDefine(true);
}