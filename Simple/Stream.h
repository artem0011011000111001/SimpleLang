#pragma once

#ifndef _STREAM_H_
#define _STREAM_H_

#include "Module.h"

#include "Simple_defines.h"

using namespace Simple;

namespace Simple_libs {

	namespace Stream {

		class Stream : public Module_Base {
			void InitVars();
			void InitFuncs();
		public:
			void Init() override;
		};
	}
}

#endif // _STREAM_H_