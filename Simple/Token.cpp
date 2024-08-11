#include "Token.h"

using namespace Simple;

Token::Token(TokenType type, WString text) : type(type), text(text) {}

WString Token::enum_in_string() const {
	switch (type) {
	case TokenType::NUM:
		return L"NUMBER " + text;

	case TokenType::HEX_NUM:
		return L"HEX_NUMBER " + text;

	case TokenType::WORD:
		return L"WORD " + text;

	case TokenType::TEXT:
		return L"TEXT " + text;

	case TokenType::PLUS:
		return L"PLUS";

	case TokenType::MINUS:
		return L"MINUS";

	case TokenType::STAR:
		return L"STAR";

	case TokenType::SLASH:
		return L"SLASH";

	case TokenType::STARSTAR:
		return L"STARSTAR";

	case TokenType::PLUSPLUS:
		return L"PLUSPLUS";

	case TokenType::MINUSMINUS:
		return L"MINUSMINUS";

	case TokenType::LT:
		return L"LT";

	case TokenType::LTEQ:
		return L"LTEQ";

	case TokenType::GT:
		return L"GT";

	case TokenType::GTEQ:
		return L"GTEQ";

	case TokenType::EXCL:
		return L"EXCL";

	case TokenType::EXCLEQ:
		return L"EXCLEQ";

	case TokenType::BAR:
		return L"BAR";

	case TokenType::BARBAR:
		return L"BARBAR";

	case TokenType::AMP:
		return L"AMP";

	case TokenType::AMPAMP:
		return L"AMPAMP";

	case TokenType::LPAREN:
		return L"LPAREN";

	case TokenType::RPAREN:
		return L"RPAREN";

	case TokenType::LBRACE:
		return L"LBRACE";

	case TokenType::RBRACE:
		return L"RBRACE";

	case TokenType::EQ:
		return L"EQ";

	case TokenType::SEMICOLON:
		return L"SEMICOLON";

	case TokenType::COLON:
		return L"COLON";

	case TokenType::EQEQ:
		return L"EQEQ";

	case TokenType::COMMA:
		return L"COMMA";

	case TokenType::CONST:
		return L"CONST";

	case TokenType::IF:
		return L"IF";

	case TokenType::ELSE:
		return L"ELSE";

	case TokenType::DO:
		return L"DO";

	case TokenType::WHILE:
		return L"WHILE";

	case TokenType::FOR:
		return L"FOR";

	case TokenType::BREAK:
		return L"BREAK";

	case TokenType::CONTINUE:
		return L"CONTINUE";

	case TokenType::IMPORT:
		return L"IMPORT";

	case TokenType::SWITCH:
		return L"SWITCH";

	case TokenType::CASE:
		return L"CASE";

	case TokenType::_DEFAULT:
		return L"DEFAULT";

	case TokenType::END_OF_FILE:
		return L"END_OF_FILE";

	default:
		return L"Unknown token";
	}
}

TokenType Token::getType() const {
	return type;
}

void Token::setType(TokenType newType) {
	type = newType;
}

WString Token::getText() const {
	return text;
}

void Token::setText(WString newText) {
	text = newText;
}
