#pragma once

#ifndef _MATH_H_
#define _MATH_H_

#include "Module.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Math {

		class Math : public Module_Base {
			void InitVars();
			void InitFuncs();
			static double _factorial(double n);
			static double _mean(std::vector<double>& values);
		public:
			void Init() override;
		};
	}
}

#endif // _MATH_H_