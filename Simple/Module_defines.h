#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define CHECK_TYPE(type, arg) if (!equals_type(type, arg->GetTypeInString())) throw Simple_Error(L"required " + WString(type) +  L" instead of " + arg->GetTypeInString())

//#define _DEFINE_FUNCTION(designator, funcbody) \
//        _DEFINE_FUNCTION_WITH_ARGS(designator, funcbody, any_args)

#define _DEFINE_FUNCTION    \
        Functions::RegisterDynamicFunction

#define _DEFINE_VAR_NUM(name, value, is_const) Variables::Set(name, Variable(NUMBER(value), is_const));
#define _DEFINE_VAR_STR(name, value, is_const) Variables::Set(name, Variable(STRING(value), is_const));

#define _ADD_STRUCT(name, fields_params) \
        Structs::Add(name, copy_fields_params(fields_params))

#define _DEFINE_STRUCT_WITH_CONSTRUCTOR(name, funcbody, argscount, fields_params)   \
        _ADD_STRUCT(name, fields_params);                                           \
        Functions::RegisterDynamicFunction(name, funcbody, argscount)

#define _DEFINE_STRUCT(name, fields_params)                                        \
        _DEFINE_STRUCT_WITH_CONSTRUCTOR(name, BLOCK(args) {                        \
            Vars_t fields;                                                         \
            auto field_decl_it = fields_params.begin();                            \
            for (auto& arg : args) {                                               \
                if (arg->GetTypeInString() !=                                      \
                    field_decl_it->second.type) throw Simple_Error("Invalid type");\
                fields.emplace(field_decl_it->first, arg->clone());                \
                ++field_decl_it;                                                   \
            }                                                                      \
            return STRUCT(name, fields);                                           \
        }, (int)fields_params.size(), fields_params);

#define IMPORT(_module_name) ImportStatement(_module_name).execute()

#define BLOCK(designator) [&](Args_t designator) -> VALUE

#define HAND_OVER_ARGS(...)                 \
    ([&]() -> Args_t {                      \
        Args_t _args;                       \
        (_args.push_back(__VA_ARGS__));     \
        return MOVE(_args);                 \
    })()

#define CALL(funcname, args) Functions::Get(funcname, (int)args.size())->execute(args)

#define MOVE std::move

#define FIELD_INFO       Field_info

//#define FIELD_DECL(...)         \
//    ([&]() -> Fields_decl_t {   \
//        Fields_decl_t _fields_; \
//        (_fields_.insert(__VA_ARGS__));            \
//        return MOVE(_fields_);  \
//    })()

#define DECL_FIELDS _DECL_FIELDS
        /*return MOVE(fields); \
    }*/


#define FIELD(name, type, is_immutable, default_value) \
    fields[name] = Field_info(type, is_immutable, default_value)

#define DEF_STRUCT(name) \
    struct name { \
        Fields_decl_t fields; \
        std::function<void(Args_t)> __constructor; \
        int __argscount; \
        void init() { \
            _ADD_STRUCT(L###name, fields); \
            _DEFINE_FUNCTION(L###name, BLOCK(args) { __constructor(MOVE(args)); return STRUCT(L###name, to_vars_t(fields)); }, __argscount); \
        } \
        name() {

#define CONSTRUCTOR(body, argscount)             \
        __argscount = argscount;                 \
        __constructor = [&](Args_t args) -> void \
            body;                     

#define END_STRUCT(name) \
        } \
    }; \
    static name name##struct; name##struct.init();
        
#endif // _MODULE_DEFINES_H_