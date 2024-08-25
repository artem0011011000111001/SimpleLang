#include "ArgParams.h"
#include "Simple_defines.h"
#include "Expressions.h"

using namespace Simple;

ArgParams::ArgParams(WString name, bool isConst, ExpressionPtr defaultValue)
	: name(name), isConst(isConst), defaultValue(MOVE(defaultValue)) {}
