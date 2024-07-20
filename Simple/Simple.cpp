#include "Simple.h"
#include <iostream>

void Simple::RegisterStandartModules() {
	RegisterModule<Simple::Math>("Math");
	RegisterModule<Simple::Stream>("Stream");
	RegisterModule<Simple::Type>("Type");
	RegisterModule<Simple::Time>("Time");
}

void Simple::compile(std::string& code) {
	RegisterStandartModules();

	Lexer lexer(code);

	Parser parser(lexer.tokenize());

	try {
		auto res = CREATE_PTR<GlobalBlockStatement>(parser.parse());
		res->execute();
	}
	catch (const Simple_Error& ex) {
		std::cout << ex.what() << " on line: " << (ex.line() == simple_npos ? "Unknown line" : std::to_string(ex.line()));
	}
	catch (const BreakStatement&) {
		std::cout << "No break processing found";
	}
	catch (const ContinueStatement&) {
		std::cout << "No continue processing found";
	}
	catch (ValuePtr&) {
		std::cout << "No return processing found";
	}
}