#pragma once

#ifndef _STREAM_H_
#define _STREAM_H_

#include "Module.h"
#include "StreamFunctions.h"
#include "Functions.h"
#include "Variables.h"

#include "Simple_defines.h"

namespace Simple {
	class Stream : public Module_Base {
		void InitVars();
		void InitFuncs();
	public:
		void Init() override;
	};
}

#endif // _STREAM_H_