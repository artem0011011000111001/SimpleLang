#include "System.h"

#include <fstream>
#include <array>

using namespace Simple;

void Simple_libs::System::System::Init() {
	InitStructs();
	InitVars();
	InitFuncs();
}

void Simple_libs::System::System::InitVars() {
	
}

void Simple_libs::System::System::InitFuncs() {
	
	_DEFINE_FUNCTION_WITH_ARGS("file_exists", BLOCK(args) {
		return BOOL(std::filesystem::exists(std::filesystem::path(args[0]->AsString())));
	}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("create_file", BLOCK(args) {
		String path = args[0]->AsString();

		std::filesystem::path file_path(path);

		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		if (!file) {
			THROW_FILE_ERROR("Failed to create file: " + path);
		}
		return VOID;
	}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("delete_file", BLOCK(args) {
		String path = args[0]->AsString();

		std::filesystem::path file_path(path);

		if (!std::filesystem::exists(file_path)) {
			THROW_FILE_ERROR("File does not exist: " + path);
		}

		std::error_code ec;
		std::filesystem::remove(file_path, ec);
		if (ec) {
			THROW_FILE_ERROR("Failed to delete file: " + path + " Error: " + ec.message());
		}

		return VOID;
	}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("write", BLOCK(args) {
		std::filesystem::path file_path(args[0]->AsString());

		write_file_content(file_path, args[1]->AsString());

		return VOID;
	}, 2);

	_DEFINE_FUNCTION_WITH_ARGS("write_append", BLOCK(args) {
		std::filesystem::path file_path(args[0]->AsString());

		write_file_content(file_path, args[1]->AsString(), true);

		return VOID;
	}, 2);

	_DEFINE_FUNCTION_WITH_ARGS("read", BLOCK(args) {
		return STRING(read_file_content(args[0]->AsString()));
	}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("run", BLOCK(args) {
		String command = args[0]->AsString();
		std::array<char, 128> buffer;
		String result;

		#ifdef _WIN32
			FILE* pipe = _popen(command.c_str(), "r");
		#else
			FILE* pipe = popen(command.c_str(), "r");
		#endif

		if (!pipe) {
			throw STRING("Failed to run command: " + command);
		}
		while (fgets(buffer.data(), (int)buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}

		#ifdef _WIN32
			_pclose(pipe);
		#else
			pclose(pipe);
		#endif

		return STRING(result);
	}, 1);

	_DEFINE_FUNCTION_WITH_ARGS("upload_to_git", BLOCK(args) {
		CALL("run", HAND_OVER_ARGS(STRING("git add .")));
		CALL("run", HAND_OVER_ARGS(STRING("git commit -m \"" + args[0]->AsString() + "\"")));
		CALL("run", HAND_OVER_ARGS(STRING("git push origin master")));
		return VOID;
	}, 1);

	_DEFINE_FUNCTION("clear_rep", BLOCK(args) {
		CALL("run", HAND_OVER_ARGS(STRING("git pull origin master")));
		CALL("run", HAND_OVER_ARGS(STRING("git fetch origin master")));
		return VOID;
	});
}

void Simple_libs::System::System::InitStructs() {
	Fields_decl_t file_error_fields_info = {
		{ "error",      ValueType::_STRING }
	};
	_DEFINE_STRUCT("FileError", file_error_fields_info);


	Fields_decl_t file_info_fields_info = {
		{ "path",      ValueType::_STRING },
		{ "name",      ValueType::_STRING },
		{ "extension", ValueType::_STRING },
		{ "content",   ValueType::_STRING },
		{ "size",      ValueType::_NUMBER }
	};
	_ADD_STRUCT("file_info", file_info_fields_info);

	_DEFINE_STRUCT_WITH_CONSTRUCTOR("file_info", BLOCK(args) {
		Val_map fields;
		String path = args[0]->AsString();

		std::filesystem::path file_path(path);

		if (std::filesystem::exists(file_path)) {
			fields.emplace("path",      STRING(file_path.string()));
			fields.emplace("name",      STRING(file_path.stem().string()));
			fields.emplace("extension", STRING(file_path.extension().string()));
			fields.emplace("content",   STRING(read_file_content(file_path)));
			fields.emplace("size",		NUMBER((double)std::filesystem::file_size(file_path)));
		} else {
			THROW_FILE_ERROR("File does not exist: " + path);
		}
		return STRUCT("file_info", fields);
	}, 1);
}

String Simple_libs::System::System::read_file_content(const std::filesystem::path& file_path) {
	std::ifstream file(file_path, std::ios::in | std::ios::binary);
	if (!file) {
		THROW_FILE_ERROR("Failed to open file: " + file_path.string());
	}

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	String content(size, '\0');
	if (!file.read(&content[0], size)) {
		THROW_FILE_ERROR("Failed to read file content: " + file_path.string());
	}

	return content;
}

void Simple_libs::System::System::write_file_content(const std::filesystem::path& file_path, const String& content, bool isAppend) {
	std::ofstream file(file_path, std::ios::out | (isAppend ? std::ios::app : std::ios::trunc));
	if (!file) {
		THROW_FILE_ERROR("Failed to open file for writing: " + file_path.string());
	}

	file << content;
	if (!file) {
		THROW_FILE_ERROR("Failed to write content to file: " + file_path.string());
	}
}