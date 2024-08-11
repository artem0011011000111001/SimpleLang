#pragma once

#ifndef _SIMPLE_ERROR_H_
#define _SIMPLE_ERROR_H_

#include "Simple_typedefs.h"
#include "Simple_defines.h"

#include <string>
#include <vector>

namespace Simple {

	struct Simple_Error {
	private:
		WString error_text;
		size_t error_line;
	public: ///////////////////////
		Simple_Error(String error_text = "", size_t error_line = simple_npos);
		Simple_Error(WString error_text = L"", size_t error_line = simple_npos); ///////////////////////

		WString what() const;

		size_t line() const;
	};
}

#endif // !_SIMPLE_ERROR_H_
