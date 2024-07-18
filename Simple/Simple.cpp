#include <iostream>
#include "Simple.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, Simple::Token& type) {
	os << type.enum_in_string();
	return os;
}

std::string ReadCodeFromFile(std::string path) {
	std::string code;
	std::string line;
	try
	{
		std::ifstream file(path);

		while (std::getline(file, line)) {
			code += line + "\n";
		}

		file.close();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	return code;
}

void RegisterStandartModules() {
	Simple::RegisterModule<Simple::Math>   ("Math");
	Simple::RegisterModule<Simple::Stream> ("Stream");
	Simple::RegisterModule<Simple::Type>   ("Type");
}

int main()
{ 
	using namespace Simple;

	RegisterStandartModules();

	std::string code = ReadCodeFromFile("code.txt");

	Simple::Lexer lex(code);

	try {
		auto tokens = lex.tokenize();
		/*for (auto& token : tokens) {
			std::cout << token << std::endl;
		}*/

		std::cout << "=======================\n\n";
		
		const StatementPtr exprs = std::make_unique<GlobalBlockStatement>(Parser(tokens).parse());

		exprs->execute();

		std::cout << "\n\n=======================\n";

		// std::cout << exprs->to_string();
	}
	catch (const Simple_Error& ex) {
		std::cout << ex.what() << " on line: " << (ex.line() == simple_npos ? "Unknown line" : std::to_string(ex.line()));
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
}