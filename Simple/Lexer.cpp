#include "Lexer.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

Lexer::Lexer(std::string& input) : input(input), tokens(), pos(0), length(input.length()) {}

std::list<Token> Lexer::tokenize() {
	while (pos < length) {
		char current = peek(0);
		if (std::isdigit(current)) tokenizeNumber();
		else if (std::isalpha(current) || current == '_' || current == '$') tokenizeWord();
		else if (current == '\"') tokenizeText();
		else if (current == '#') tokenizeHexNumber();
		//else if (current == '\n') tokenizeNewLine();
		else if (indexOfUnMap(OPERATORS, current) != simple_npos) tokenizeOperator();
		else next();
	}
	return tokens;
}

void Lexer::tokenizeNumber() {
	std::string buffer;
	char current = peek(0);
	while (true) {
		if (current == '.') {
			if (indexOf(buffer, '.') != simple_npos) throw Simple_Error("Two dots in float number");
		}
		else if (!std::isdigit(current)) 
			break;
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::NUMBER, buffer);
}

void Lexer::tokenizeHexNumber() {
	next(); // skip #
	std::string buffer;
	char current = peek(0);
	while (IsHex(current)) {
		buffer.push_back(current);
		current = next();
	}
	addToken(TokenType::HEX_NUMBER, buffer);
}

void Lexer::tokenizeWord() {
	std::string buffer;
	char current = peek(0);
	while (IsWord(current)) {
		buffer.push_back(current);
		current = next();
	}
	if (buffer == "print")
		addToken(TokenType::PRINT);

	else if (buffer == "const")
		addToken(TokenType::CONST);

	else if (buffer == "if")
		addToken(TokenType::IF);

	else if (buffer == "else")
		addToken(TokenType::ELSE);

	else if (buffer == "do")
		addToken(TokenType::DO);

	else if (buffer == "while")
		addToken(TokenType::WHILE);

	else if (buffer == "for")
		addToken(TokenType::FOR);

	else if (buffer == "break")
		addToken(TokenType::BREAK);

	else if (buffer == "continue")
		addToken(TokenType::CONTINUE);

	else if (buffer == "import")
		addToken(TokenType::IMPORT);

	else if (buffer == "switch")
		addToken(TokenType::SWITCH);

	else if (buffer == "case")
		addToken(TokenType::CASE);

	else if (buffer == "default")
		addToken(TokenType::DEFAULT);

	else if (buffer == "func")
		addToken(TokenType::FUNC);

	else if (buffer == "return")
		addToken(TokenType::RETURN);

	else addToken(TokenType::WORD, buffer);
}

void Lexer::tokenizeText() {
	next(); // skip opening "
	std::string buffer;
	char current = peek(0);
	while (current != '\"') {
		if (current == '\\') {
			current = next();
			switch (current) {
			case '\"':
				current = next();
				buffer.push_back('\"');
				continue;
			case 'n':
				current = next();
				buffer.push_back('\n');
				continue;
			case 't':
				current = next();
				buffer.push_back('\t');
				continue;
			default:
				buffer.push_back('\\');
				continue;
			}
		}
		buffer.push_back(current);
		current = next();
	}
	next(); // skip closing "
	addToken(TokenType::TEXT, buffer);
}

void Lexer::tokenizeOperator() {
	char current = peek(0);
	if (current == '/') {
		if (peek(1) == '/') {
			next();
			next();
			tokenizeComment();
			return;
		}
		else if (peek(1) == '*') {
			next();
			next();
			tokenizeMultilineComment();
			return;
		}
	}
	std::string buffer;
	while (true) {
		std::string text = buffer;
		if (OPERATORS.find(text + current) == OPERATORS.end() && !OPERATORS.empty()) {
			addToken(OPERATORS.at(text));
			return;
		}
		buffer.push_back(current);
		current = next();
	}
}

void Lexer::tokenizeComment() {
	char current = peek(0);
	while (indexOf("\n\r\0", current) == simple_npos) {
		current = next();
	}
}

void Lexer::tokenizeMultilineComment() {
	char current = peek(0);
	while (!(current == '*' && peek(1) == '/')) {
		if (current == '\0') throw Simple_Error("Missing close tag");
		current = next();
	}
	next(); // skip *
	next(); // skip /
}

//void Lexer::tokenizeNewLine() {
//	addToken(TokenType::NEWLINE);
//	next(); // skip \n
//}