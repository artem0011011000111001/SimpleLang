#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define _DEFINE_FUNCTION_CLASS(funcname, funcbody)					\
struct funcname : Function {										\
	ValuePtr execute(std::vector<ValuePtr> args) override {			\
		return funcbody(std::move(args));							\
	}																\
																	\
	FunctionPtr clone() const override {							\
		return std::make_unique<funcname>();						\
	}																\
};
#define _DEFINE_FUNCTION(designator, funcclass) Functions::Set(designator, CREATE_PTR<funcclass>())

#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS(funcname, funcbody, designator) \
	_DEFINE_FUNCTION_CLASS(funcname, funcbody)								\
	_DEFINE_FUNCTION(designator, funcname)

#endif // _MODULE_DEFINES_H_