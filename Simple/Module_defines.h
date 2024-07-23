#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define _DEFINE_FUNCTION_CLASS(funcname, funcbody, argscount)               \
struct funcname : Function {                                                \
    ValuePtr execute(std::vector<ValuePtr> args) override {                 \
        if (argscount != any_args) {                                        \
            size_t param_count = args.size();                               \
            if (param_count != argscount) throw Simple_Error("Expected " +  \
                std::to_string(argscount) +                                 \
                " args(s) instead of " + std::to_string(param_count));      \
        }                                                                   \
        return funcbody(std::move(args));                                   \
    }                                                                       \
                                                                            \
    FunctionPtr clone() const override {                                    \
        return std::make_unique<funcname>();                                \
    }                                                                       \
};

#define _DEFINE_FUNCTION(designator, funcclass) \
        Functions::Set(designator, CREATE_PTR<funcclass>())

#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS(funcname, funcbody, designator) \
        _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, designator, any_args)

#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, designator, argscount) \
	    _DEFINE_FUNCTION_CLASS(funcname, funcbody, argscount)				                     \
	    _DEFINE_FUNCTION(designator, funcname)

#define _DEFINE_FUNCTION_S(funcname, funcbody) \
        _DEFINE_FUNCTION_WITH_ARGS_S(funcname, funcbody, any_args)

#define _DEFINE_FUNCTION_WITH_ARGS_S(funcname, funcbody, argscount) \
        _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, #funcname, argscount)

#define _DEFINE_VAR_NUM(name, value, is_const) Variables::Set(name, Variable(NUMBER(value), is_const));
#define _DEFINE_VAR_STR(name, value, is_const) Variables::Set(name, Variable(STRING(value), is_const));

#endif // _MODULE_DEFINES_H_