#include "Parser.h"
#include "Simple_Error.h"

using namespace Simple;

StatementPtr Parser::block() {
	BlockStatement block;
	consume(TokenType::LBRACE);
	while (!match(TokenType::RBRACE)) {
		block.add(getNextStatement());
	}
	return CREATE_PTR<BlockStatement>(std::move(block));
}

SwitchBlockStatement Parser::switchBlock() {
	SwitchBlockStatement block;
	consume(TokenType::LBRACE);
	bool IsFirst = true;

	while (!match(TokenType::RBRACE)) {
		block.add(std::move(caseStatement()));
		IsFirst = false;
	}
	if (IsFirst) throw Simple_Error("Expected case or default");

	return block;
}