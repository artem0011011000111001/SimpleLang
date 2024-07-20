#pragma once

#ifndef _TOKEN_TYPE_H_
#define _TOKEN_TYPE_H_

namespace Simple {

	enum class TokenType {
		// Types
		NUMBER,
		HEX_NUMBER,
		WORD,
		TEXT,

		// Keywords
		CONST,
		IF,
		ELSE,
		DO,
		WHILE,
		FOR,
		BREAK,
		CONTINUE,
		IMPORT,
		SWITCH,
		CASE,
		DEFAULT,
		FUNC,
		RETURN,

		// Operators
		PLUS,          //   +
		MINUS,         //   -
		STAR,	       //   *
		SLASH,	       //   /
		STARSTAR,	   //   **
		PLUSPLUS,	   //   ++
		MINUSMINUS,	   //   --
		PLUSEQ,		   //   +=
		MINUSEQ,	   //   -=
		STAREQ,		   //   *=
		SLASHEQ,	   //   /=
		STARSTAREQ,	   //   **=
		LPAREN,	       //   (
		RPAREN,	       //   )
		EQ,		       //   =
		SEMICOLON,     //   ;
		EQEQ,		   //   ==
		LT,			   //   <
		LTEQ,          //   <=
		GT,			   //   >
		GTEQ,		   //   >=
		EXCL,		   //   !
		EXCLEQ,		   //   !=
		BAR,		   //   |
		BARBAR,		   //   ||
		AMP,           //   &
		AMPAMP,		   //   &&
		LBRACE,        //   {
		RBRACE,		   //   }
		COMMA,		   //   ,

		END_OF_FILE
	};
}
#endif // !_TOKEN_TYPE_H_