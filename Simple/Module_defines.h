#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define _DEFINE_FUNCTION_CLASS(funcname, funcbody)                          \
struct funcname : Function {                                                \
    ValuePtr execute(std::vector<ValuePtr> args) override {                 \
        /*return funcbody([&args]() -> std::vector<ValuePtr> {                \
            std::vector<ValuePtr> result;                                   \
            std::transform(                                                 \
                args.begin(),                                               \
                args.end(),                                                 \
                std::back_inserter(result),                                 \
                [](Variable& arg) { return std::move(arg.value); }          \
            );                                                              \
            return std::move(result);                                       \
        }());*/                                                             \
        return funcbody(std::move(args));                                   \
    }                                                                       \
                                                                            \
    FunctionPtr clone() const override {                                    \
        return std::make_unique<funcname>();                                \
    }                                                                       \
};

#define _DEFINE_FUNCTION(designator, funcclass) Functions::Set(designator, CREATE_PTR<funcclass>())

#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS(funcname, funcbody, designator) \
	    _DEFINE_FUNCTION_CLASS(funcname, funcbody)							\
	    _DEFINE_FUNCTION(designator, funcname)

#define _DEFINE_VAR_NUM(name, value, is_const) Variables::Set(name, Variable(CREATE_PTR<NumberValue>(value), is_const));
#define _DEFINE_VAR_STR(name, value, is_const) Variables::Set(name, Variable(CREATE_PTR<StringValue>(value), is_const));

#endif // _MODULE_DEFINES_H_