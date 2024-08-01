#pragma once

#ifndef _TYPE_H_
#define _TYPE_H_

#include "Module.h"
#include "Functions.h"
#include "Variables.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Type {

		class Type : public Module_Base {
			void InitVars();
			void InitFuncs();
			void InitStruct();
		public:
			void Init() override;
		};
	}
}

#endif // _TYPE_H_