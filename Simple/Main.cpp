#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>

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
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
	return code;
}

int main() { 
	//setlocale(LC_ALL, "ru");
	std::string code = ReadCodeFromFile("code.txt");

	Simple::compile(code);

	return 0;
}