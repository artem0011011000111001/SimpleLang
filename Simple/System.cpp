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
			FILE* pipe = popen(uni_to_ascii(command).c_str(), "r");
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
	
	DEF_STRUCT(FileError)

	FIELD(L"error", L"str", false, NOT_VALUE);

	CONSTRUCTOR({

		fields[L"error"].value = STRING(args[0]->AsString());

		}, 1)

		END_STRUCT(FileError);


	/*static Fields_decl_t FileErrorFields = DECL_FIELDS({
		{ L"error", FIELD_INFO(L"str") }
		});

	_DEFINE_STRUCT(L"FileError", FileErrorFields);*/


	DEF_STRUCT(file_info)
		
	FIELD(L"path",      L"str", false, NOT_VALUE);
	FIELD(L"name",      L"str", false, NOT_VALUE);
	FIELD(L"extension", L"str", false, NOT_VALUE);
	FIELD(L"content",   L"str", false, NOT_VALUE);
	FIELD(L"size",		L"num", false, NOT_VALUE);

	CONSTRUCTOR({

		WString path = args[0]->AsString();

		std::filesystem::path file_path(path);

		if (std::filesystem::exists(file_path)) {
			fields[L"path"].value	   = STRING(file_path.wstring());
			fields[L"name"].value	   = STRING(file_path.stem().wstring());
			fields[L"extension"].value = STRING(file_path.extension().wstring());
			fields[L"content"].value   = CALL(L"read", HAND_OVER_ARGS(STRING(file_path.wstring())));
			fields[L"size"].value      = NUMBER((double)std::filesystem::file_size(file_path));
		}
		else THROW_FILE_ERROR(L"File does not exist: " + path);

		}, 1)

		END_STRUCT(file_info);

	/*static Fields_decl_t file_infoFields = DECL_FIELDS({
		{ L"path",		FIELD_INFO(L"str") },
		{ L"name",		FIELD_INFO(L"str") },
		{ L"extension",	FIELD_INFO(L"str") },
		{ L"content",	FIELD_INFO(L"str") },
		{ L"size",		FIELD_INFO(L"num") }
		});

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
	}, 1, file_infoFields);*/
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