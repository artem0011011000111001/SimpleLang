#include "Parser.h"
#include "Simple_Error.h"

using namespace Simple;

Token Parser::get(const size_t relativePosition) {
	const size_t position = pos + relativePosition;
	if (position >= size) return EOF_TOKEN;
	return tokens.at(position);
}

bool Parser::match(const TokenType type) {
	const Token CurrentToken = get(0);
	if (type != CurrentToken.getType()) return false;
	pos++;
	return true;
}

Token Parser::consume(const TokenType type) {
	if (!match(type)) {
		throw Simple_Error("Expected " + Token(type, "").enum_in_string());
	}
	return get(-1);
}

int Parser::stoihex(const std::string& hex)
{
	int decimal = 0;
	size_t length = hex.length();

	for (int i = 0; i < length; ++i) {
		char hexDigit = hex[length - 1 - i];
		int value = 0;

		if (hexDigit >= '0' && hexDigit <= '9') {
			value = hexDigit - '0';
		}
		else if (hexDigit >= 'A' && hexDigit <= 'F') {
			value = 10 + (hexDigit - 'A');
		}
		else if (hexDigit >= 'a' && hexDigit <= 'f') {
			value = 10 + (hexDigit - 'a');
		}

		decimal += static_cast<int>(value * pow(16, i));
	}

	return decimal;
}