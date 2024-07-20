#pragma once

#ifndef _TYPE_H_
#define _TYPE_H_

#include "Module.h"
#include "TypeFunctions.h"
#include "Functions.h"
#include "Variables.h"

#include "Simple_defines.h"

namespace Simple {
	class Type : public Module_Base {
		void InitVars();
		void InitFuncs();
	public:
		void Init() override;
	};
}

#endif // _TYPE_H_