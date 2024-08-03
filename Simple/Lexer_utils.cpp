#include "Lexer.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

void Lexer::addToken(const TokenType type) {
	addToken(type, "");
}

void Lexer::addToken(const TokenType type, const String text) {
	tokens.push_back(Token(type, text));
}

char Lexer::peek(const size_t relativePosition) const {
	const size_t position = pos + relativePosition;
	if (position >= length) return '\0';
	return input[position];
}

char Lexer::next() {
	pos++;
	return peek(0);
}

bool Lexer::IsWord(const char c) {
	return std::isalnum(c) || c == '_' || c == '$';
}

bool Lexer::IsHex(const char c) {
	return std::isdigit(c) || indexOf(String("abcdef"), std::tolower(c)) != simple_npos;
}

//template<class _Ty, class _Ty2>
//size_t Lexer::indexOf(const _Ty& collection, const _Ty2& val) {
//	size_t count = 0;
//	for (const auto& el : collection) {
//		if (el == val) return count;
//		count++;
//	}
//	return simple_npos;
//}
//
//template<class _Ty, class _Ty2>
//size_t Lexer::indexOfUnMap(const std::unordered_map<String, _Ty>& collection, const _Ty2& val) {
//	size_t count = 0;
//	for (const auto& el : collection)
//	{
//		for (const auto& c : el.first)
//		{
//			if (c == val) return count;
//			count++;
//		}
//	}
//	return simple_npos;
//}