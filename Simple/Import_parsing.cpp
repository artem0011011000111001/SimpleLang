#include "Parser.h"
#include "Simple_defines.h"

using namespace Simple;

StatementPtr Parser::Import() {
	StatementPtr result = std::make_unique<ImportStatement>(consume(TokenType::WORD).getText());
	CHECK_END_STR;
	return result;
}