#include "Simple.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <sstream>
#include <locale>
#pragma warning(disable : 4996)

#undef _WIN32

size_t Simple::GetSizeOfFile(const WString& path) {
#ifdef _WIN32
	struct _stat fileinfo;
	_wstat(path.c_str(), &fileinfo);
#else
	struct stat fileinfo;
	String narrow_path = uni_to_ascii(path);

	if (stat(narrow_path.c_str(), &fileinfo) != 0) {

		return 0;
	}
#endif

	return fileinfo.st_size;
}

//template<class _StrTy>
//inline WString Simple::ReadCodeFromFile(_StrTy& path) {
//
//	WString final__;
//
////#ifdef _WIN32
////	std::ifstream fin;
////	fin.open(path);
////
////	if (fin.is_open()) {
////		std::ostringstream oss;
////		oss << fin.rdbuf();
////		String str = oss.str();
////		const char* buf = str.c_str();
////		int length = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
////		wchar_t* ptr = new wchar_t[length];
////
////		MultiByteToWideChar(CP_ACP, 0, buf, -1, ptr, length);
////
////		final__ = ptr;
////		delete[] ptr;
////	}
////	else
////		std::cout << "file not exists";
////#else
//
//	std::wifstream file(path, std::ios::binary);
//
//	if (!file) {
//		std::wcout << L"File on path \"" + WString(path.begin(), path.end()) + "\" not exist";
//	}
//
//	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
//
//	std::wstring line;
//	while (std::getline(file, line))
//		final__ += line;
//
//	return final__;
//}

void Simple::RegisterStandartModules() {
	RegisterModule<Simple_libs::Math::Math>(L"Math");
	RegisterModule<Simple_libs::Type::Type>(L"Type");
	RegisterModule<Simple_libs::Time::Time>(L"Time");
	RegisterModule<Simple_libs::Exception::Exception>(L"Exception");
	RegisterModule<Simple_libs::System::System>(L"System");
}

void Simple::compile(WString& code) {
	std::locale::global(std::locale("C"));
	std::locale::global(std::locale("en_US.UTF-8"));
	RegisterStandartModules();
	Functions::CreateStandartFunctions();


	try {
		static Vec<Ptr<GlobalBlockStatement>> results;

		Lexer lexer(code);

		Parser parser(lexer.tokenize());

		auto res = CREATE_PTR<GlobalBlockStatement>(parser.parse());
		res->execute();

		results.push_back(MOVE(res));
	}
	catch (const Simple_Error& ex) {
		std::wcout << ex.what() << L" on line: " << (ex.line() == simple_npos ? L"Unknown line" : std::to_wstring(ex.line()));
	}
	catch (const BreakStatement&) {
		std::wcout << L"No break processing found";
	}
	catch (const ContinueStatement&) {
		std::wcout << L"No continue processing found";
	}
	catch (ReturnStatement::ReturnValue&) {
		std::wcout << L"No return processing found";
	}
	catch (ValuePtr& ThrowValue) {
		std::wcout << L"Unhandled " + ThrowValue->GetTypeInString() + L" exception";
	}
}