#pragma once

#ifndef _MATH_H_
#define _MATH_H_

#include "Module.h"
#include "MathFunctions.h"
#include "Functions.h"
#include "Variables.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Math {

		class Math : public Module_Base {
			void InitVars();
			void InitFuncs();
		public:
			void Init() override;
		};
	}
}

#endif // _MATH_H_