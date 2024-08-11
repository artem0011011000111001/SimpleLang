#include "RawVariable.h"

using namespace Simple;

RawVariable::RawVariable(ExpressionPtr value, bool isConst) : value(MOVE(value)) {}