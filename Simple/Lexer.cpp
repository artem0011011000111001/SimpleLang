#include "Lexer.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

#include <cwctype>

using namespace Simple;

Lexer::Lexer(WString& input) : input(input), tokens(), pos(0), length(input.length()) {}

std::list<Token> Lexer::tokenize() {
    while (pos < length) {
        WChar current = peek(0);
        if (std::iswdigit(current))
            if (peek(1) == L'd') tokenizeDigit();
            else tokenizeNumber();

        else if (std::iswalpha(current) || current == L'_' || current == L'$') tokenizeWord();
        else if (current == L'\"') tokenizeText();
        else if (current == L'\'') tokenizeChar();
        else if (current == L'#') tokenizeHexNumber();
        else if (current == L'\n') tokenizeNewLine();
        else if (check_operator(OPERATORS, current) != simple_npos) tokenizeOperator();
        else next();
    }
    return tokens;
}

void Lexer::tokenizeNumber() {
    WString buffer;
    WChar current = peek(0);
    while (true) {
        if (current == L'.') {
            if (indexOf(buffer, L'.') != simple_npos) throw Simple_Error("Two dots in float number");
            if (!std::iswdigit(peek(1))) throw Simple_Error("Expected digit after .");
        }
        else if (!std::iswdigit(current))
            break;
        buffer.push_back(current);
        current = next();
    }
    addToken(TokenType::NUM, buffer);
}

void Lexer::tokenizeDigit() {
    addToken(TokenType::DIGIT_, WString(1, peek(0)));
    next(); // skip digit
    next(); // skip d
}

void Lexer::tokenizeHexNumber() {
    next(); // skip #
    WString buffer;
    WChar current = peek(0);
    while (IsHex(current)) {
        buffer.push_back(current);
        current = next();
    }
    addToken(TokenType::HEX_NUM, buffer);
}

void Lexer::tokenizeWord() {
    WString buffer;
    WChar current = peek(0);
    while (IsWord(current)) {
        buffer.push_back(current);
        current = next();
    }

    if (buffer == L"const")
        addToken(TokenType::CONST);

    else if (buffer == L"if")
        addToken(TokenType::IF);

    else if (buffer == L"else")
        addToken(TokenType::ELSE);

    else if (buffer == L"do")
        addToken(TokenType::DO);

    else if (buffer == L"while")
        addToken(TokenType::WHILE);

    else if (buffer == L"for")
        addToken(TokenType::FOR);

    else if (buffer == L"break")
        addToken(TokenType::BREAK);

    else if (buffer == L"continue")
        addToken(TokenType::CONTINUE);

    else if (buffer == L"import")
        addToken(TokenType::IMPORT);

    else if (buffer == L"switch")
        addToken(TokenType::SWITCH);

    else if (buffer == L"case")
        addToken(TokenType::CASE);

    else if (buffer == L"default")
        addToken(TokenType::_DEFAULT);

    else if (buffer == L"func")
        addToken(TokenType::FUNC);

    else if (buffer == L"return")
        addToken(TokenType::RETURN);

    else if (buffer == L"struct")
        addToken(TokenType::STRUCT);

    else if (buffer == L"field")
        addToken(TokenType::_FIELD);

    else if (buffer == L"immutable")
        addToken(TokenType::IMMUTABLE);

    else if (buffer == L"try")
        addToken(TokenType::TRY);

    else if (buffer == L"catch")
        addToken(TokenType::CATCH);

    else if (buffer == L"throw")
        addToken(TokenType::THROW);

    else if (buffer == L"foreach")
        addToken(TokenType::FOREACH);

    else if (buffer == L"true")
        addToken(TokenType::_TRUE);

    else if (buffer == L"false")
        addToken(TokenType::_FALSE);

    else if (buffer == L"void")
        addToken(TokenType::_VOID_);

    else if (buffer == L"destruct")
        addToken(TokenType::DESTRUCT);

    else if (buffer == L"enum")
        addToken(TokenType::ENUM);

    else addToken(TokenType::WORD, buffer);
}

void Lexer::tokenizeText() {
    next(); // skip opening "
    WString buffer;
    WChar current = peek(0);
    while (current != L'\"') {
        if (current == L'\0')
            throw Simple_Error("No closing found \"");
        if (current == L'\\') {
            current = next();
            switch (current) {
            case L'\"':
                current = next();
                buffer.push_back(L'\"');
                continue;
            case L'n':
                current = next();
                buffer.push_back(L'\n');
                continue;
            case L't':
                current = next();
                buffer.push_back(L'\t');
                continue;
            default:
                buffer.push_back(L'\\');
                continue;
            }
        }
        buffer.push_back(current);
        current = next();
    }
    next(); // skip closing "
    addToken(TokenType::TEXT, buffer);
}

void Lexer::tokenizeChar() {
    next(); // skip opening '
    addToken(TokenType::CHAR_, WString(1, peek(0)));
    next(); // skip WChar
    if (peek(0) != L'\'')
        throw Simple_Error("Many symbols in symbol type");
    next(); // skip closing '
}

void Lexer::tokenizeOperator() {
    WChar current = peek(0);
    if (current == L'/') {
        if (peek(1) == L'/') {
            next();
            next();
            tokenizeComment();
            return;
        }
        else if (peek(1) == L'*') {
            next();
            next();
            tokenizeMultilineComment();
            return;
        }
    }
    WString buffer;
    while (true) {
        WString text = buffer;
        if (OPERATORS.find(text + current) == OPERATORS.end() && !OPERATORS.empty()) {
            addToken(OPERATORS.at(text));
            return;
        }
        buffer.push_back(current);
        current = next();
    }
}

void Lexer::tokenizeComment() {
    WChar current = peek(0);
    while (indexOf(L"\n\r\0", current) == simple_npos) {
        current = next();
    }
}

void Lexer::tokenizeMultilineComment() {
    WChar current = peek(0);
    while (!(current == L'*' && peek(1) == L'/')) {
        if (current == L'\0') throw Simple_Error("Missing close tag");
        current = next();
    }
    next(); // skip *
    next(); // skip /
}

void Lexer::tokenizeNewLine() {
    addToken(TokenType::NEW_LINE);
    next(); // skip \n
}