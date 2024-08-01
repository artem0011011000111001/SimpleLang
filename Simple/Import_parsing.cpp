#include "Parser.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::Import() {

	StatementPtr result;
	if (match(TokenType::WORD))
		result = CREATE_PTR<ImportStatement>(get(-1).getText());
	else result = CREATE_PTR<ImportStatement>(consume(TokenType::TEXT).getText(), true);
	CHECK_END_STR;
	return result;
}