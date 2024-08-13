#pragma once

#ifndef _TOKEN_TYPE_H_
#define _TOKEN_TYPE_H_

namespace Simple {

	enum class TokenType {
		// Types
		NUM,
		HEX_NUM,
		WORD,
		TEXT,
		CHAR_,
		DIGIT_,

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
		_DEFAULT,
		FUNC,
		RETURN,
		STRUCT,
		_FIELD,
		IMMUTABLE,
		TRY,
		CATCH,
		THROW,
		FOREACH,
		_TRUE,
		_FALSE,
		_VOID_,
		DESTRUCT,
		ENUM,

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
		DOT,           //   .
		LSBRACKET,     //   [
		RSBRACKET,     //   ]
		COLON,		   //   :
		ELLIPSIS,      //   ...

		NEW_LINE,
		END_OF_FILE
	};
}
#endif // !_TOKEN_TYPE_H_