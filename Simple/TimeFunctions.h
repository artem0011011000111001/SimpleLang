#pragma once

#ifndef _TIME_FUNCTIONS_H_
#define _TIME_FUNCTIONS_H_

#include "Function.h"

namespace Simple {

	ValuePtr Now(std::vector<ValuePtr> args);

	ValuePtr Sleep(std::vector<ValuePtr> args);

}

#endif // _TIME_FUNCTIONS_H_