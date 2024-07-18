#pragma once

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "TokenType.h"

#include <string>

namespace Simple {

	struct Token {
	private:
		TokenType type;
		std::string text;

	public:
		Token() = default;

		Token(TokenType type, std::string text);

		std::string enum_in_string() const;

		TokenType getType() const;

		void setType(TokenType newType);

		std::string getText() const;

		void setText(std::string newText);
	};
}

#endif // !_TOKEN_H_
