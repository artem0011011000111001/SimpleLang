#include "Simple_Iterator.h"

using namespace Simple;

Simple_Iterator::Simple_Iterator(ValuePtr* ptr)
	: ptr(ptr) {}

ValuePtr& Simple_Iterator::operator*() const { 
	return *ptr;
}

ValuePtr* Simple_Iterator::operator->() {
	return ptr;
}

Simple_Iterator& Simple_Iterator::operator++() {
	ptr++;
	return *this;
}

Simple_Iterator Simple_Iterator::operator++(int) {
	Simple_Iterator temp = *this;
	++(*this);
	return temp;
}

bool Simple_Iterator::operator==(const Simple_Iterator& other) const {
	return ptr == other.ptr;
}

bool Simple_Iterator::operator!=(const Simple_Iterator& other) const {
	return ptr != other.ptr;
}

