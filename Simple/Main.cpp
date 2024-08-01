#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <sysinfoapi.h>
#include <windows.h>
#include <stdio.h>
SYSTEM_INFO siSysInfo;

GetSystemInfo(&siSysInfo);
#pragma comment(lib, "user32.lib")

int main() { 
	std::string code = Simple::ReadCodeFromFile("code.simple");

	//Simple::compile(code);

	return 0;
}