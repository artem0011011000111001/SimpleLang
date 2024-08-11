#pragma once

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "Simple_typedefs.h"
#include "Field_decl.h"


namespace Simple {

	struct Structs {
	private:
		static Structs_t structs;

	public:

		static bool IsExist(const WString& key);

		static Fields_decl_t Get(const WString& key);

		static void Add(const WString& key, Fields_decl_t fields);

		static bool _equals(const WString& key1, const WString& key2);
	};
}

#endif // _STRUCTS_H_