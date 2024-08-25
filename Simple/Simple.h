#pragma once

#ifndef _SIMPLE_LANGUAGE_
#define _SIMPLE_LANGUAGE_

#include "AST.h"
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "Expressions.h"
#include "Function.h"
#include "Module.h"
#include "Values.h"
#include "Function.h"
#include "Functions.h"
#include "Variable.h"
#include "Variables.h"
#include "Utils.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Simple_typedefs.h"
#include "Simple_Iterator.h"
#include "Libs.h"

#include <iostream>
#include <fstream>
#include <codecvt>
#include <sstream>
#include <locale>
#pragma warning(disable : 4996)

namespace Simple {
	size_t GetSizeOfFile(const WString& path);

	template<class _StrTy>
	WString ReadCodeFromFile(_StrTy& path) {

		WString final__;

		//#ifdef _WIN32
		//	std::ifstream fin;
		//	fin.open(path);
		//
		//	if (fin.is_open()) {
		//		std::ostringstream oss;
		//		oss << fin.rdbuf();
		//		String str = oss.str();
		//		const char* buf = str.c_str();
		//		int length = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
		//		wchar_t* ptr = new wchar_t[length];
		//
		//		MultiByteToWideChar(CP_ACP, 0, buf, -1, ptr, length);
		//
		//		final__ = ptr;
		//		delete[] ptr;
		//	}
		//	else
		//		std::cout << "file not exists";
		//#else

		std::wifstream file(path, std::ios::binary);

		if (!file) {
			std::wcout << L"File on path \"" + WString(path.begin(), path.end()) + L"\" not exist";
		}

		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

		std::wstring line;
		while (std::getline(file, line))
			final__ += line;

		return final__;
	}

	void RegisterStandartModules();
	void compile(WString& code);
}

#endif // _SIMPLE_LANGUAGE_