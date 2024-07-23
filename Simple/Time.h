#pragma once

#ifndef _TIME_H_
#define _TIME_H_

#include "Module.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Time {

		class Time : public Module_Base {
			void InitVars();
			void InitFuncs();
		public:
			void Init() override;
		};
	}
}

#endif // _TIME_H_