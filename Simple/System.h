#pragma once

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "Module.h"

#include "Simple_defines.h"

#include <filesystem>

#define THROW_FILE_ERROR(msg) throw CALL(L"FileError", HAND_OVER_ARGS(STRING(msg)))

using namespace Simple;

namespace Simple_libs {

	namespace System {

		class System : public Module_Base {
			void InitVars();
			void InitFuncs();
			void InitStructs();

			WString read_file_content(const std::filesystem::path& file_path);
			void write_file_content(const std::filesystem::path& file_path, const WString& content, bool isAppend = false);
		public:
			void Init() override;
		};
	}
}

#endif // _SYSTEM_H_