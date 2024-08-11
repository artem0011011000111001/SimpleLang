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
        return std::move(_args);            \
    })()

#define CALL(funcname, args) Functions::Get(funcname, (int)args.size())->execute(args)

#define MOVE std::move

#define FIELD Field_decl

#define FIELD_DECL(...)        \
    ([&]() -> Fields_decl_t {  \
        Fields_decl_t fields;  \
        __VA_ARGS__;           \
        return MOVE(fields);   \
    })()
        
#endif // _MODULE_DEFINES_H_