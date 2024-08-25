#include "Method_info.h"
#include "ArgParams.h"

using namespace Simple;

RawMethod_info::RawMethod_info(ArgsParams_t args_params, bool is_any_args, StatementPtr body, bool isPrivate)
	: args_params(MOVE(args_params)), is_any_args(is_any_args), body(MOVE(body)), isPrivate(isPrivate) {}