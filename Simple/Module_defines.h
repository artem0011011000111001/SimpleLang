#pragma once

#ifndef _MODULE_DEFINES_H_
#define _MODULE_DEFINES_H_

#define CHECK_TYPE(type, arg) if (!equals_type(type, arg->GetTypeInString())) throw Simple_Error("Invalid type")

#define _DEFINE_FUNCTION(designator, funcbody) \
        _DEFINE_FUNCTION_WITH_ARGS(designator, funcbody, any_args)

#define _DEFINE_FUNCTION_WITH_ARGS(designator, funcbody, argscount) \
        Functions::RegisterDynamicFunction(designator, funcbody, argscount)

#define _DEFINE_VAR_NUM(name, value, is_const) Variables::Set(name, Variable(NUMBER(value), is_const));
#define _DEFINE_VAR_STR(name, value, is_const) Variables::Set(name, Variable(STRING(value), is_const));

#define _ADD_STRUCT(name, fields_decl) \
        Structs::Add(name, fields_decl)

#define _DEFINE_STRUCT_WITH_CONSTRUCTOR   \
        Functions::RegisterDynamicFunction

#define _DEFINE_STRUCT(name, fields_decl)                                     \
        _DEFINE_STRUCT_WITH_CONSTRUCTOR(name, [fields_decl](Args_t args) {    \
            Val_map fields;                                                   \
            Structs::Add(name, fields_decl);                                  \
            auto field_decl_it = fields_decl.begin();                         \
            for (auto& arg : args) {                                          \
                if (IdentifyValueType(arg->GetTypeInString()) !=              \
                    field_decl_it->second) throw Simple_Error("Invalid type");\
                fields.emplace(field_decl_it->first, arg->clone());           \
                ++field_decl_it;                                              \
            }                                                                 \
            return STRUCT(name, fields);                                      \
        }, fields_decl.size());                                               \

#define IMPORT(_module_name) ImportStatement(_module_name).execute()

#define BLOCK(designator) [&](Args_t designator)

#define HAND_OVER_ARGS(...)                 \
    ([&]() -> Args_t {                      \
        Args_t _args;                       \
        (_args.push_back(__VA_ARGS__));     \
        return std::move(_args);            \
    })()

#define CALL(funcname, args) Functions::Get(funcname)->execute(args)

#define MOVE std::move
        
#endif // _MODULE_DEFINES_H_