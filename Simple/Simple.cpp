#include "Simple.h"
#include <iostream>

void Simple::RegisterStandartModules() {
	RegisterModule<Simple_libs::Math::Math>("Math");
	RegisterModule<Simple_libs::Stream::Stream>("Stream");
	RegisterModule<Simple_libs::Type::Type>("Type");
	RegisterModule<Simple_libs::Time::Time>("Time");
}

void Simple::compile(std::string& code) {
	std::locale::global(std::locale("C"));
	RegisterStandartModules();
	Functions::CreateStandartFunctions();

	try {
		Lexer lexer(code);

		Parser parser(lexer.tokenize());

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