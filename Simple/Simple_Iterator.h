#pragma once

#ifndef _SIMPLE_ITERATOR_H_
#define _SIMPLE_ITERATOR_H_

#include "Values.h"
#include "Simple_typedefs.h"

namespace Simple {

	class Simple_Iterator {
		
		ValuePtr* ptr;

	public:
		Simple_Iterator(ValuePtr* data);

		ValuePtr& operator*() const;
		ValuePtr* operator->();

		Simple_Iterator& operator++();

		Simple_Iterator operator++(int);

		bool operator==(const Simple_Iterator& other) const;
		bool operator!=(const Simple_Iterator& other) const;
	};
}

#endif // _SIMPLE_ITERATOR_H_