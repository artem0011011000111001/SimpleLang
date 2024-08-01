#include "Simple.h"
#include <iostream>
#include <fstream>

std::string Simple::ReadCodeFromFile(std::string path) {
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
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
	return code;
}

void Simple::RegisterStandartModules() {
	RegisterModule<Simple_libs::Math::Math>("Math");
	RegisterModule<Simple_libs::Stream::Stream>("Stream");
	RegisterModule<Simple_libs::Type::Type>("Type");
	RegisterModule<Simple_libs::Time::Time>("Time");
	RegisterModule<Simple_libs::Exception::Exception>("Exception");
}

void Simple::HandleErrors(void(*func)(std::string), std::string code) {
	try {
		func(code);
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
	catch (ReturnStatement::ReturnValue&) {
		std::cout << "No return processing found";
	}
	catch (ValuePtr& ThrowValue) {
		std::cout << "Unhandled " + ThrowValue->GetTypeInString() + " exception";
	}
}

void Simple::compile(std::string& code) {
	std::locale::global(std::locale("C"));
	RegisterStandartModules();
	Functions::CreateStandartFunctions();

	HandleErrors([](std::string code) {
		Lexer lexer(code);

		Parser parser(lexer.tokenize());

		auto res = CREATE_PTR<GlobalBlockStatement>(parser.parse());
		res->execute();
		}, code);
}