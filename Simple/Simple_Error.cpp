#include "Simple_Error.h"

using namespace Simple;

Simple_Error::Simple_Error(String error_text, size_t error_line) 
	: error_text(WString(error_text.begin(), error_text.end())), error_line(error_line) {}

Simple_Error::Simple_Error(WString error_text, size_t error_line)
	: error_text(error_text), error_line(error_line) {}

WString Simple_Error::what() const {
	return error_text;
}

size_t Simple_Error::line() const {
	return error_line;
}