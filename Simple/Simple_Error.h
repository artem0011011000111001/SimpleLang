#pragma once

#ifndef _SIMPLE_ERROR_H_
#define _SIMPLE_ERROR_H_

#include "Simple_defines.h"

#include <string>
#include <vector>

namespace Simple {
	struct Simple_Error : std::exception {
	private:
		std::string error_text;
		size_t error_line;
	public:///////////////////////
		Simple_Error(std::string error_text = "", size_t error_line = simple_npos); ///////////////////////

		size_t line() const;
	};
}

#endif // !_SIMPLE_ERROR_H_
