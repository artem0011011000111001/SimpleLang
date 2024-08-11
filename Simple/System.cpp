#include "System.h"

#include <fstream>
#include <array>
#include <cwchar>

using namespace Simple;

void Simple_libs::System::System::Init() {
	InitStructs();
	InitVars();
	InitFuncs();
}

void Simple_libs::System::System::InitVars() {
	
}

void Simple_libs::System::System::InitFuncs() {
	
	_DEFINE_FUNCTION(L"file_exists", BLOCK(args) {
		return BOOL(std::filesystem::exists(std::filesystem::path(args[0]->AsString())));
	}, 1);

	_DEFINE_FUNCTION(L"create_file", BLOCK(args) {
		WString path = args[0]->AsString();

		std::filesystem::path file_path(path);

		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		if (!file) {
			THROW_FILE_ERROR(L"Failed to create file: " + path);
		}
		return VOID;
	}, 1);

	_DEFINE_FUNCTION(L"delete_file", BLOCK(args) {
		WString path = args[0]->AsString();

		std::filesystem::path file_path(path);

		if (!std::filesystem::exists(file_path)) {
			THROW_FILE_ERROR(L"File does not exist: " + path);
		}

		std::error_code ec;
		std::filesystem::remove(file_path, ec);
		if (ec) {
			THROW_FILE_ERROR(L"Failed to delete file: " + path + L" Error: " + WString(ec.message().begin(), ec.message().end()));
		}

		return VOID;
	}, 1);

	_DEFINE_FUNCTION(L"write", BLOCK(args) {
		std::filesystem::path file_path(args[0]->AsString());

		write_file_content(file_path, args[1]->AsString());

		return VOID;
	}, 2);

	_DEFINE_FUNCTION(L"write_append", BLOCK(args) {
		std::filesystem::path file_path(args[0]->AsString());

		write_file_content(file_path, args[1]->AsString(), true);

		return VOID;
	}, 2);

	_DEFINE_FUNCTION(L"read", BLOCK(args) {
		return STRING(read_file_content(args[0]->AsString()));
	}, 1);

	_DEFINE_FUNCTION(L"run", BLOCK(args) {
		WString command = args[0]->AsString();
		std::array<WChar, 128> buffer;
		WString result;

		#ifdef _WIN32
			FILE* pipe = _wpopen(command.c_str(), L"r");
		#else
			FILE* pipe = wpopen(command.c_str(), L"r");
		#endif

		if (!pipe) {
			throw STRING(L"Failed to run command: " + command);
		}
		while (fgetws(buffer.data(), (int)buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}

		#ifdef _WIN32
			_pclose(pipe);
		#else
			pclose(pipe);
		#endif

		return STRING(result);
	}, 1);

	_DEFINE_FUNCTION(L"upload_to_git", BLOCK(args) {
		CALL(L"run", HAND_OVER_ARGS(STRING(L"git add .")));
		CALL(L"run", HAND_OVER_ARGS(STRING(L"git commit -m \"" + args[0]->AsString() + L"\"")));
		CALL(L"run", HAND_OVER_ARGS(STRING(L"git push origin master")));
		return VOID;
	}, 1);

	_DEFINE_FUNCTION(L"clear_rep", BLOCK(args) {
		CALL(L"run", HAND_OVER_ARGS(STRING(L"git pull origin master")));
		CALL(L"run", HAND_OVER_ARGS(STRING(L"git fetch origin master")));
		return VOID;
	}, 0);
}

void Simple_libs::System::System::InitStructs() {

	_DEFINE_STRUCT(L"FileError", FIELD_DECL(
		fields.emplace(L"error", FIELD(L"str"))
	));

	_DEFINE_STRUCT_WITH_CONSTRUCTOR(L"file_info", BLOCK(args) {
		Fields_t fields;
		WString path = args[0]->AsString();

		std::filesystem::path file_path(path);

		if (std::filesystem::exists(file_path)) {
			fields.emplace(L"path",      STRING(file_path.wstring()));
			fields.emplace(L"name",      STRING(file_path.stem().wstring()));
			fields.emplace(L"extension", STRING(file_path.extension().wstring()));
			fields.emplace(L"content",   STRING(read_file_content(file_path)));
			fields.emplace(L"size",		 NUMBER((double)std::filesystem::file_size(file_path)));
		} else {
			THROW_FILE_ERROR(L"File does not exist: " + path);
		}
		return STRUCT(L"file_info", fields);
	}, 1, FIELD_DECL(
		L"path",		L"str",
		L"name",		L"str",
		L"extension",	L"str",
		L"content",		L"str",
		L"size",		L"num"
	));
}

WString Simple_libs::System::System::read_file_content(const std::filesystem::path& file_path) {
	std::wifstream file(file_path, std::ios::in | std::ios::binary);
	if (!file) {
		THROW_FILE_ERROR(L"Failed to open file: " + file_path.wstring());
	}

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	WString content(size, '\0');
	if (!file.read(&content[0], size)) {
		THROW_FILE_ERROR(L"Failed to read file content: " + file_path.wstring());
	}

	return content;
}

void Simple_libs::System::System::write_file_content(const std::filesystem::path& file_path, const WString& content, bool isAppend) {
	std::wofstream file(file_path, std::ios::out | (isAppend ? std::ios::app : std::ios::trunc));
	if (!file) {
		THROW_FILE_ERROR(L"Failed to open file for writing: " + file_path.wstring());
	}

	file << content;
	if (!file) {
		THROW_FILE_ERROR(L"Failed to write content to file: " + file_path.wstring());
	}
}