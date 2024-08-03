#include "Token.h"

using namespace Simple;

Token::Token(TokenType type, String text) : type(type), text(text) {}

String Token::enum_in_string() const {
	switch (type) {
	case TokenType::NUM:
		return "NUMBER " + text;

	case TokenType::HEX_NUM:
		return "HEX_NUMBER " + text;

	case TokenType::WORD:
		return "WORD " + text;

	case TokenType::TEXT:
		return "TEXT " + text;

	case TokenType::PLUS:
		return "PLUS";

	case TokenType::MINUS:
		return "MINUS";

	case TokenType::STAR:
		return "STAR";

	case TokenType::SLASH:
		return "SLASH";

	case TokenType::STARSTAR:
		return "STARSTAR";

	case TokenType::PLUSPLUS:
		return "PLUSPLUS";

	case TokenType::MINUSMINUS:
		return "MINUSMINUS";

	case TokenType::LT:
		return "LT";

	case TokenType::LTEQ:
		return "LTEQ";

	case TokenType::GT:
		return "GT";

	case TokenType::GTEQ:
		return "GTEQ";

	case TokenType::EXCL:
		return "EXCL";

	case TokenType::EXCLEQ:
		return "EXCLEQ";

	case TokenType::BAR:
		return "BAR";

	case TokenType::BARBAR:
		return "BARBAR";

	case TokenType::AMP:
		return "AMP";

	case TokenType::AMPAMP:
		return "AMPAMP";

	case TokenType::LPAREN:
		return "LPAREN";

	case TokenType::RPAREN:
		return "RPAREN";

	case TokenType::LBRACE:
		return "LBRACE";

	case TokenType::RBRACE:
		return "RBRACE";

	case TokenType::EQ:
		return "EQ";

	case TokenType::SEMICOLON:
		return "SEMICOLON";

	case TokenType::COLON:
		return "COLON";

	case TokenType::EQEQ:
		return "EQEQ";

	case TokenType::COMMA:
		return "COMMA";

	case TokenType::CONST:
		return "CONST";

	case TokenType::IF:
		return "IF";

	case TokenType::ELSE:
		return "ELSE";

	case TokenType::DO:
		return "DO";

	case TokenType::WHILE:
		return "WHILE";

	case TokenType::FOR:
		return "FOR";

	case TokenType::BREAK:
		return "BREAK";

	case TokenType::CONTINUE:
		return "CONTINUE";

	case TokenType::IMPORT:
		return "IMPORT";

	case TokenType::SWITCH:
		return "SWITCH";

	case TokenType::CASE:
		return "CASE";

	case TokenType::DEFAULT:
		return "DEFAULT";

	case TokenType::END_OF_FILE:
		return "END_OF_FILE";

	default:
		return "Unknown token";
	}
}

TokenType Token::getType() const { 
	return type; 
}

void Token::setType(TokenType newType) { 
	type = newType;
}

String Token::getText() const {
	return text;
}

void Token::setText(String newText) { 
	text = newText;
}