#include "Simple.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <sstream>

#pragma warning(disable : 4996)

#undef NUMBER
#undef DIGIT
#undef CHAR
#undef STRING
#undef BOOL
#undef VOID
#undef ARRAY
#undef TRUE
#undef FALSE

#include <Windows.h>

size_t GetSizeOfFile(const std::wstring& path)
{
	struct _stat fileinfo;
	_wstat(path.c_str(), &fileinfo);
	return fileinfo.st_size;
}


WString Simple::ReadCodeFromFile(WString& path) {

	//setlocale(LC_ALL, ".1251");

	WString final__;
	std::ifstream fin;
	fin.open(path);

	if (fin.is_open()) {
		std::ostringstream oss;
		oss << fin.rdbuf();
		String str = oss.str();
		const char* buf = str.c_str();

		//std::cout << buf << std::endl;

		int length = MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
		wchar_t* ptr = new wchar_t[length];
		//std::cout << length << std::endl;
		MultiByteToWideChar(CP_ACP, 0, buf, -1, ptr, length);
		final__= ptr;
	}
	else
		std::cout << "file not exists";

	return final__;
	/*std::wifstream wif(path);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();*/
	/*std::wstring wstr;
    std::ifstream file (path.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    size_t size = (size_t)file.tellg();
    file.seekg (0, std::ios::beg);
    char* buffer = new char[size];
    file.read (buffer, size);
    wstr = (wchar_t*)buffer;
	std::cout << buffer;
    file.close();
    delete[] buffer;
	return L"";*/

	//WString buffer;

	/*std::basic_ifstream<wchar_t> fin(path);
	std::wstring str{};
	std::getline(fin, str, L'\0');
	return str;*/
	//std::wstring buffer;            // stores file contents
	//FILE* f = _wfopen(path.c_str(), L"rtS, ccs=UTF-8");

	//// Failed to open file
	//if (f == NULL)
	//{
	//	// ...handle some error...
	//	return buffer;
	//}

	//size_t filesize = GetSizeOfFile(path);

	//// Read entire file contents in to memory
	//if (filesize > 0)
	//{
	//	buffer.resize(filesize);
	//	size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
	//	buffer.resize(wchars_read);
	//	buffer.shrink_to_fit();
	//}

	//fclose(f);

	//return buffer;
	/*WString code;
	WString line;
	try {

		const std::locale empty_locale = std::locale::empty();
		typedef std::codecvt_utf8<wchar_t> converter_type;
		const converter_type* converter = new converter_type;
		const std::locale utf8_locale = std::locale(empty_locale, converter);

		std::wifstream file(path);
		file.imbue(utf8_locale);

		while (std::getline(file, line)) {
			code += line + L"\n";
		}

		file.close();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
	return code;*/
}

void Simple::RegisterStandartModules() {
	RegisterModule<Simple_libs::Math::Math>(L"Math");
	RegisterModule<Simple_libs::Stream::Stream>(L"Stream");
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