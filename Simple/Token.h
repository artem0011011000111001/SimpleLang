#pragma once

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "TokenType.h"
#include "Simple_typedefs.h"

#include <string>

namespace Simple {

	struct Token {
	private:
		TokenType type;
		String text;

	public:
		Token() = default;

		Token(TokenType type, String text);

		String enum_in_string() const;

		TokenType getType() const;

		void setType(TokenType newType);

		String getText() const;

		void setText(String newText);
	};
}

#endif // !_TOKEN_H_
