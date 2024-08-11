#include "Parser.h"
#include "Simple_Error.h"

using namespace Simple;

Token Parser::get(const size_t relativePosition) {
	const size_t position = pos + relativePosition;
	if (position >= size) return EOF_TOKEN;
	return tokens.at(position);
}

void Parser::skip_newlines() {
	while (get(0).getType() == TokenType::NEW_LINE) {
		pos++, line++;
	}
}

bool Parser::match(const TokenType type) {
	skip_newlines();

	const Token CurrentToken = get(0);
	if (type != CurrentToken.getType()) return false;
	pos++;

	return true;
}

Token Parser::consume(const TokenType type) {
	skip_newlines();

	const Token CurrentToken = get(0);
	if (type != CurrentToken.getType()) {
		throw Simple_Error(L"Expected " + Token(type, L"").enum_in_string(), line);
	}
	pos++;

	return CurrentToken;
}

int Parser::stoihex(const WString& hex) {
	int decimal = 0;
	size_t length = hex.length();

	for (size_t i = 0; i < length; ++i) {
		wchar_t hexDigit = hex[length - 1 - i];
		int value = 0;

		if (hexDigit >= L'0' && hexDigit <= L'9') {
			value = hexDigit - L'0';
		}
		else if (hexDigit >= L'A' && hexDigit <= L'F') {
			value = 10 + (hexDigit - L'A');
		}
		else if (hexDigit >= L'a' && hexDigit <= L'f') {
			value = 10 + (hexDigit - L'a');
		}

		decimal += static_cast<int>(value * pow(16, i));
	}

	return decimal;
}