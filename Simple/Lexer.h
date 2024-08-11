#pragma once

#ifndef _LEXER_H_
#define _LEXER_H_

#include "Token.h"
#include "TokenType.h"
#include "Simple_typedefs.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

#include <unordered_map>
#include <list>
#include <string>

namespace Simple {
	class Lexer
	{
	private:

		/*const WWString OPERATORS_CHARS = "+-()=;<>";
		const TokenType OPERATORS_TOKENS[10] = {
			TokenType::PLUS, TokenType::MINUS,
			TokenType::STAR, TokenType::SLASH,
			TokenType::LPAREN, TokenType::RPAREN,
			TokenType::EQ, TokenType::SEMICOLON,
			TokenType::LT, TokenType::GT
		};*/

		const WStr_map<TokenType> OPERATORS = {
			{L"+",      TokenType::PLUS},
			{L"-",      TokenType::MINUS},
			{L"*",      TokenType::STAR},
			{L"/",      TokenType::SLASH},
			{L"**",     TokenType::STARSTAR},
			{L"++",     TokenType::PLUSPLUS},
			{L"--",     TokenType::MINUSMINUS},
			{L"+=",     TokenType::PLUSEQ},
			{L"-=",     TokenType::MINUSEQ},
			{L"*=",     TokenType::STAREQ},
			{L"/=",     TokenType::SLASHEQ},
			{L"**=",    TokenType::STARSTAREQ},
			{L"(",      TokenType::LPAREN},
			{L")",      TokenType::RPAREN},
			{L"=",      TokenType::EQ},
			{L";",      TokenType::SEMICOLON},
			{L"<",      TokenType::LT},
			{L">",      TokenType::GT},
			{L"!",      TokenType::EXCL},
			{L"!=",     TokenType::EXCLEQ},
			{L"&",      TokenType::AMP},
			{L"&&",     TokenType::AMPAMP},
			{L"|",      TokenType::BAR},
			{L"||",     TokenType::BARBAR},
			{L"==",     TokenType::EQEQ},
			{L"<=",     TokenType::LTEQ},
			{L">=",     TokenType::GTEQ},
			{L"{",      TokenType::LBRACE},
			{L"}",      TokenType::RBRACE},
			{L",",      TokenType::COMMA},
			{L".",      TokenType::DOT},
			{L"[",      TokenType::LSBRACKET},
			{L"]",      TokenType::RSBRACKET},
			{L":",      TokenType::COLON},
			{L"...",    TokenType::ELLIPSIS}
		};

	private:
		const WString input;
		std::list<Token> tokens;
		size_t pos;
		const size_t length;

	public:
		Lexer(WString& input);

		std::list<Token> tokenize();
	private:
		void tokenizeNumber();

		void tokenizeDigit();

		void tokenizeHexNumber();

		void tokenizeWord();

		void tokenizeText();

		void tokenizeChar();

		void tokenizeOperator();

		void tokenizeNewLine();

		void tokenizeComment();

		void tokenizeMultilineComment();

	private:

		void addToken(const TokenType type);

		void addToken(const TokenType type, const WString text);

		WChar peek(const size_t relativePostion) const;

		WChar next();

	private:
		template<class _Ty, class _Ty2>
		size_t indexOf(const _Ty& collection, const _Ty2& val) {
			size_t count = 0;
			for (const auto& el : collection) {
				if (el == val) return count;
				count++;
			}
			return simple_npos;
		}

		template<class _Ty, class _Ty2>
		size_t check_operator(const WStr_map<_Ty>& collection, const _Ty2& val) {
			size_t count = 0;
			for (const auto& el : collection)
			{
				for (const auto& c : el.first)
				{
					if (c == val) return count;
					count++;
				}
			}
			return simple_npos;
		}

		bool IsWord(const WChar c);

		bool IsHex(const WChar c);
	};
}

#endif // !_LEXER_H_
