#pragma once

#ifndef _FUNC_PARAMS_H_
#define _FUNC_PARAMS_H_

#include "Function.h"

namespace Simple {

	struct FuncParams {
		Map<int, FunctionPtr> func_bodies;

		FuncParams(Map<int, FunctionPtr> func_bodies);
		FuncParams() = default;

		FuncParams clone() const;
	};

	struct MethodParams : public FuncParams {
		bool isPrivate;

		MethodParams(Map<int, FunctionPtr> func_bodies, bool isPrivate);
		MethodParams() = default;

		MethodParams clone() const;
	};
}

#endif // _FUNC_PARAMS_H_