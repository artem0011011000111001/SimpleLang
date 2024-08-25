#pragma once

#ifndef _METHOD_INFO_H_
#define _METHOD_INFO_H_

#include "Utils.h"
#include "Expressions.h"
#include "Simple_defines.h"
#include "AST.h"

namespace Simple {

	struct RawMethod_info {
		ArgsParams_t args_params;
		bool is_any_args;
		StatementPtr body;
		bool isPrivate;

		RawMethod_info(ArgsParams_t args_params, bool is_any_args, StatementPtr body, bool isPrivate);
		RawMethod_info() = default;
	};
}

#endif // _METHOD_INFO_H_