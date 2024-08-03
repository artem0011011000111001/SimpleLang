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

		/*const String OPERATORS_CHARS = "+-()=;<>";
		const TokenType OPERATORS_TOKENS[10] = {
			TokenType::PLUS, TokenType::MINUS,
			TokenType::STAR, TokenType::SLASH,
			TokenType::LPAREN, TokenType::RPAREN,
			TokenType::EQ, TokenType::SEMICOLON,
			TokenType::LT, TokenType::GT
		};*/

		const Str_map<TokenType> OPERATORS = {
			{"+",      TokenType::PLUS},
			{"-",      TokenType::MINUS},
			{"*",      TokenType::STAR},
			{"/",      TokenType::SLASH},
			{"**",     TokenType::STARSTAR},
			{"++",     TokenType::PLUSPLUS},
			{"--",     TokenType::MINUSMINUS},
			{"+=",     TokenType::PLUSEQ},
			{"-=",     TokenType::MINUSEQ},
			{"*=",     TokenType::STAREQ},
			{"/=",     TokenType::SLASHEQ},
			{"**=",    TokenType::STARSTAREQ},
			{"(",      TokenType::LPAREN},
			{")",      TokenType::RPAREN},
			{"=",      TokenType::EQ},
			{";",      TokenType::SEMICOLON},
			{"<",      TokenType::LT},
			{">",      TokenType::GT},
			{"!",      TokenType::EXCL},
			{"!=",     TokenType::EXCLEQ},
			{"&",      TokenType::AMP},
			{"&&",     TokenType::AMPAMP},
			{"|",      TokenType::BAR},
			{"||",     TokenType::BARBAR},
			{"==",     TokenType::EQEQ},
			{"<=",     TokenType::LTEQ},
			{">=",     TokenType::GTEQ},
			{"{" ,     TokenType::LBRACE},
			{"}" ,     TokenType::RBRACE},
			{"," ,     TokenType::COMMA},
			{"." ,     TokenType::DOT},
			{"[" ,     TokenType::LSBRACKET},
			{"]" ,     TokenType::RSBRACKET},
			{":" ,     TokenType::COLON}
		};

	private:
		const String input;
		std::list<Token> tokens;
		size_t pos;
		const size_t length;

	public:
		Lexer(String& input);

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

		void addToken(const TokenType type, const String text);

		char peek(const size_t relativePostion) const;

		char next();

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
		size_t indexOfUnMap(const Str_map<_Ty>& collection, const _Ty2& val) {
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

		bool IsWord(const char c);

		bool IsHex(const char c);
	};
}

#endif // !_LEXER_H_
