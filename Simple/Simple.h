#pragma once

#ifndef _SIMPLE_LANGUAGE_
#define _SIMPLE_LANGUAGE_

#include "AST.h"
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "Expressions.h"
#include "Function.h"
#include "Module.h"
#include "Values.h"
#include "Function.h"
#include "Functions.h"
#include "Variable.h"
#include "Variables.h"
#include "Utils.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Simple_typedefs.h"
#include "Libs.h"

namespace Simple {
	static void RegisterStandartModules();
	void compile(std::string& code);
}

#endif // _SIMPLE_LANGUAGE_