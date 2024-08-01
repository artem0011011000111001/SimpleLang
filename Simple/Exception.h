#pragma once

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "Module.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Exception {

		class Exception : public Module_Base {
			void InitVars();
			void InitFuncs();
			void InitStructs();
		public:
			void Init() override;
		};
	}
}

#endif // _EXCEPTION_H_