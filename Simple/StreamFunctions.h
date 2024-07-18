#pragma once

#ifndef _STREAM_FUNCTIONS_H_
#define _STREAM_FUNCTIONS_H_

#include "Function.h"

namespace Simple {

	ValuePtr Output(std::vector<ValuePtr> args);

	ValuePtr Outputln(std::vector<ValuePtr> args);

	ValuePtr Input(std::vector<ValuePtr> args);
}

#endif // !_STREAM_FUNCTIONS_H_
