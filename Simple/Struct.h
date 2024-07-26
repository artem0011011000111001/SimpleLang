#pragma once

#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "Simple_typedefs.h"

#include <vector>
#include <string>

namespace Simple {
	struct Struct {
		std::string name;
		std::vector<std::string> field_names;
		VALUE(*constructor)(Args_t);
		Struct(const std::string& name, std::vector<std::string> field_names, VALUE(*constructor)(Args_t) = nullptr);
	};
}

#endif // _STRUCT_H_