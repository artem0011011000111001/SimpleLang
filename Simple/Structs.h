#pragma once

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "Simple_typedefs.h"

namespace Simple {

	struct Structs {
	private:
		static Structs_t structs;

	public:

		static bool IsExist(const String& key);

		static Fields_decl_t Get(const String& key);

		static void Add(const String& key, Fields_decl_t fields);

		static bool _equals(const String& key1, const String& key2);
	};
}

#endif // _STRUCTS_H_