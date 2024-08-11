#include "Lexer.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

#include <cwctype>

using namespace Simple;

void Lexer::addToken(const TokenType type) {
    addToken(type, L"");
}

void Lexer::addToken(const TokenType type, const WString text) {
    tokens.push_back(Token(type, text));
}

WChar Lexer::peek(const size_t relativePosition) const {
    const size_t position = pos + relativePosition;
    if (position >= length) return L'\0';
    return input[position];
}

WChar Lexer::next() {
    pos++;
    return peek(0);
}

bool Lexer::IsWord(const WChar c) {
    return std::iswalnum(c) || c == L'_' || c == L'$';
}

bool Lexer::IsHex(const WChar c) {
    return std::iswdigit(c) || indexOf(WString(L"abcdefABCDEF"), std::towlower(c)) != simple_npos;
}
