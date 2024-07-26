#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define _DEFINE_FUNCTION_CLASS(funcname, funcbody, argscount)               \
    Functions::RegisterDynamicFunction(#funcname, funcbody, argscount)
//struct funcname : Function {                                                \
//    VALUE execute(Args_t args) override {                                   \
//        if (argscount != any_args) {                                        \
//            size_t param_count = args.size();                               \
//            if (param_count != argscount) throw Simple_Error("Expected " +  \
//                std::to_string(argscount) +                                 \
//                " args(s) instead of " + std::to_string(param_count));      \
//        }                                                                   \
//        return funcbody(std::move(args));                                   \
//    }                                                                       \
//                                                                            \
//    FunctionPtr clone() const override {                                    \
//        return CREATE_PTR<funcname>();                                      \
//    }                                                                       \
//    Function& get_ref() override {                                          \
//        return *this;                                                       \
//    }                                                                       \
//    void set_ref(FunctionPtr& ref) override {                               \
//        if (auto castRef = dynamic_cast<funcname*>(ref.get())) {            \
//            funcbody = std::move(castRef->funcbody);                        \
//            argscount = castRef->argscount;                                 \
//        }                                                                   \
//        else {                                                              \
//            throw Simple_Error("Invalid reference type");                   \
//        }                                                                   \
//    }                                                                       \
//};

#define _DEFINE_FUNCTION(designator, funcbody) \
        _DEFINE_FUNCTION_WITH_ARGS(designator, funcbody, any_args)

#define _DEFINE_FUNCTION_WITH_ARGS(designator, funcbody, argscount) \
        Functions::RegisterDynamicFunction(designator, funcbody, argscount)

//#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS(funcname, funcbody, designator) \
//        _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, designator, any_args)
//
//#define _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, designator, argscount) \
//	    _DEFINE_FUNCTION_CLASS(funcname, funcbody, argscount)				                     \
//	    _DEFINE_FUNCTION(designator, funcname)
//
//#define _DEFINE_FUNCTION_S(funcname, funcbody) \
//        _DEFINE_FUNCTION_WITH_ARGS_S(funcname, funcbody, any_args)
//
//#define _DEFINE_FUNCTION_WITH_ARGS_S(funcname, funcbody, argscount) \
//        _DEFINE_FUNCTION_AND_FUNCTION_CLASS_WITH_ARGS(funcname, funcbody, #funcname, argscount)

#define _DEFINE_VAR_NUM(name, value, is_const) Variables::Set(name, Variable(NUMBER(value), is_const));
#define _DEFINE_VAR_STR(name, value, is_const) Variables::Set(name, Variable(STRING(value), is_const));

#define _DEFINE_STRUCT_WITH_CONSTRUCTOR(name, constructor, argscount)   \
        Functions::RegisterDynamicFunction(name, constructor, argscount);

#define _DEFINE_STRUCT(name, fields_names)                                  \
        _DEFINE_STRUCT_WITH_CONSTRUCTOR(name, [fields_names](Args_t args) { \
            std::unordered_map<std::string, ValuePtr> fields;               \
            auto fields_names_it = fields_names.begin();                    \
            for (auto& arg : args) {                                        \
                fields.emplace(*fields_names_it, arg->clone());             \
                ++fields_names_it;                                          \
            }                                                               \
            return STRUCT(name, fields);                                    \
        }, fields_names.size());                           
        
#endif // _MODULE_DEFINES_H_