#pragma once

#ifndef _STREAM_FUNCTIONS_H_
#define _STREAM_FUNCTIONS_H_

#include "Function.h"

using namespace Simple;

namespace Simple_libs {

	namespace Stream {

		VALUE Output(Args_t args);

		VALUE Outputln(Args_t args);

		VALUE Input(Args_t args);
	}
}

#endif // _STREAM_FUNCTIONS_H_
