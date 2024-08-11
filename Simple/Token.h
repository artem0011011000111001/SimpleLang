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
		WString text;

	public:
		Token() = default;

		Token(TokenType type, WString text);

		WString enum_in_string() const;

		TokenType getType() const;

		void setType(TokenType newType);

		WString getText() const;

		void setText(WString newText);
	};
}

#endif // !_TOKEN_H_
