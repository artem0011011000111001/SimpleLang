#include "AST.h"
#include "Simple_Error.h"
#include "Module.h"
#include "Simple.h"

// #include <algorithm>
// #include <codecvt>
// #include <Windows.h>
#include <algorithm>
#include <locale>

using namespace Simple;

ImportStatement::ImportStatement(WString key, bool isPath) : key(key), isPath(isPath) {}

void ImportStatement::execute() {

	/*// SetCurrentDirectory(L"D:\\Projects\\MYFOLDER\\C++\\Simple");

	/*const char* path = "\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.39.33519\\bin\\Hostx64\\x64\\cl.exe\"";

	if (std::system(String("\"" + String(path) + "\" /EHsc /Fo\"" + module_name + ".obj\" \"" + module_name + ".cpp\"").c_str()) != 0)
		throw Simple_Error("Compilation \"" + module_name + "\" failed");

	//std::wstring module_path = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(module_name);
	String dllName = module_name + ".dll";
	HMODULE hLib = LoadLibraryA(dllName.c_str());

	if (!hLib) {
		std::cout << GetLastError() << "\n";
		throw Simple_Error("Failed to load \"" + module_name + "\"");
	}

	typedef void (*InitFunc)();

	InitFunc InitAll = (InitFunc)GetProcAddress(hLib, "InitAll");

	if (!InitAll) {
		throw Simple_Error("In module \"" + module_name + "\" not defined initialization function");
		FreeLibrary(hLib);
	}

	InitAll();*/
	if (std::find(connected_modules.begin(), connected_modules.end(), key) == connected_modules.end()) {
		if (isPath) {
			WString code = ReadCodeFromFile(key);
			compile(code);
		}
		else {
			auto Module = CreateModuleByName::getInstance().createInstance(key);

			if (Module)
				Module->Init();
			else
				throw Simple_Error(L"\"" + key + L"\" not found");
		}
		connected_modules.push_back(key);
	}
}

WStr_vec ImportStatement::connected_modules;