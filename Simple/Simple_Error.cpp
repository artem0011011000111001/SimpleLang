#include "Simple_Error.h"

using namespace Simple;

Simple_Error::Simple_Error(String error_text, size_t error_line) 
	: std::exception(error_text.c_str()), error_text(error_text), error_line(error_line) {}

size_t Simple_Error::line() const {
	return error_line;
}