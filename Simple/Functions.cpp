#include "Functions.h"
#include "Function.h"
#include "Values.h"
#include "Simple_Error.h"

#include <iostream>
#include <sstream>

using namespace Simple;

bool Functions::IsExist(const WString& key, int argsCount) {
    auto find = functions.find(key);

    if (find != functions.end()) {

        if (argsCount == not_specified_args)
            return true;

        auto* func_bodies = &find->second.func_bodies;
        if (func_bodies->find(argsCount) != func_bodies->end() || func_bodies->find(any_args) != func_bodies->end())
            return true;
    }
    return false;
}

FunctionPtr Functions::Get(const WString& key, int argsCount) {

    if (IsExist(key, argsCount)) {

        auto find = functions.find(key);

        if (find != functions.end()) {

            auto func = CheckAndGetFunc(find->second, argsCount);

            if (func)
                return MOVE(func);
        }
    }
    throw Simple_Error(L"Function \"" + key + L"\" with " + std::to_wstring(argsCount) + L" args not defined");
}

FuncParams Functions::Get(const WString& key) {
    if (IsExist(key)) {
        return functions.find(key)->second.clone();
    }
    throw Simple_Error(L"Function \"" + key + L"\" not defined");
}

void Functions::Set(const WString& key, FunctionPtr func, int argsCount) {
    functions[key].func_bodies[argsCount] = MOVE(func);
}

FunctionPtr Functions::CreateDynamicFunction(std::function<VALUE(Args_t)> funcbody) {
    class DynamicFunction : public Function {
        std::function<VALUE(Args_t)> funcbody;
    public:
        DynamicFunction(std::function<VALUE(Args_t)> func)
            : funcbody(MOVE(func)) {}

        ValuePtr execute(Args_t args) override {
            return funcbody(MOVE(args));
        }

        FunctionPtr clone() const override {
            return CREATE_PTR<DynamicFunction>(funcbody);
        }
    };

    return CREATE_PTR<DynamicFunction>(funcbody);
}

void Functions::RegisterDynamicFunction(const WString& name, std::function<VALUE(Args_t)> funcbody, const int argscount) {

    /*class DynamicFunction : public Function {
        std::function<VALUE(Args_t)> funcbody;
        int argscount;
    public:
        DynamicFunction(std::function<VALUE(Args_t)> func, const int argscount)
            : funcbody(MOVE(func)), argscount(argscount) {}

        ValuePtr execute(Args_t args) override {
            return funcbody(MOVE(args));
        }

        FunctionPtr clone() const override {
            return CREATE_PTR<DynamicFunction>(funcbody, argscount);
        }
    };*/

    Set(name, CreateDynamicFunction(funcbody), argscount);
}

void Functions::CreateStandartFunctions() {
    _DEFINE_FUNCTION(L"print", [](Args_t args) {
        for (auto& arg : args) {
            std::wcout << arg->AsString();
        }
        return VOID;
    }, any_args); // get: msgs*

    _DEFINE_FUNCTION(L"println", [](Args_t args) {
        for (auto& arg : args) {
            std::wcout << arg->AsString() << std::endl;
        }
        return VOID;
        }, any_args); // get: msgs*

    _DEFINE_FUNCTION(L"Array", [](Args_t args) {
        ArrayValue arr;
        for (auto& arg : args) {
            arr.AddElement(MOVE(arg));
        }
        return ARRAY(MOVE(arr));
        }, any_args); // get: values*

    _DEFINE_FUNCTION(L"print_array", [](Args_t args) {

        CHECK_TYPE(L"arr", args[0]);
        CHECK_TYPE(L"str", args[1]);
        CHECK_TYPE(L"str", args[2]);
        CHECK_TYPE(L"str", args[3]);

        auto arr = dynamic_cast<ArrayValue*>(args[0].get());

        WString separator = args[2]->AsString();

        std::wcout << args[1]->AsString();
        for (size_t i = 0, size = arr->size(); i < size; i++) {
            std::wcout << (*arr)[(int)i].AsString();
            if (i != size - 1)
                std::wcout << separator;
        }
        std::wcout << args[3]->AsString();

        return VOID;
        }, 4); // get: arr, start, separator, end

    _DEFINE_FUNCTION(L"print_array", [](Args_t args) {

        Args_t args_;
        args_.push_back(MOVE(args[0]));
        args_.push_back(STRING(L"["));
        args_.push_back(STRING(L", "));
        args_.push_back(STRING(L"]"));

        CALL(L"print_array", MOVE(args_));

        return VOID;
        }, 1); // get: arr

    _DEFINE_FUNCTION(L"input", [](Args_t args) -> VALUE {

        WString input;

        std::wcout << args.front()->AsString();

        std::wcin >> input;

        try {
            return NUMBER(strict_stod(input));
        }
        catch (const Simple_Error&) {
            return STRING(input);
        }
        }, 1);       // get: msg

    _DEFINE_FUNCTION(L"input", [](Args_t args) -> VALUE {

        Args_t args_;
        args_.push_back(EMPTY_STR);

        return CALL(L"input", MOVE(args_));
        }, 0);       // get: nothing
     
    _DEFINE_FUNCTION(L"mod", [](Args_t args) {
        return NUMBER((int)args[0]->AsDouble() % (int)args[1]->AsDouble());
        }, 2);         // get: value1, value2

    _DEFINE_FUNCTION(L"num", [](Args_t args) {
        return NUMBER(args[0]->AsDouble());
        }, 1);         // get: value

    _DEFINE_FUNCTION(L"str", [](Args_t args) {
        return STRING(args[0]->AsString());
        }, 1);         // get: value

    _DEFINE_FUNCTION(L"push", [](Args_t args) {

        CHECK_TYPE(L"arr", args[0]);
        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        arr->Push_pos(MOVE(args[1]), (int)args[2]->AsDouble());

        return ARRAY(MOVE(*arr));
        }, 3);        // get: arr, value, pos

    _DEFINE_FUNCTION(L"push", [](Args_t args) {
        CHECK_TYPE(L"arr", args[0]);
        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        arr->AddElement(MOVE(args[1]));

        return ARRAY(MOVE(*arr));
        }, 2);        // get: arr, value

    _DEFINE_FUNCTION(L"pop", [](Args_t args) {
       
        CHECK_TYPE(L"arr", args[0]);
        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        arr->Pop_pos((int)args[1]->AsDouble());

        return ARRAY(MOVE(*arr));
        }, 2);         // get: arr, pos
    
    _DEFINE_FUNCTION(L"pop", [](Args_t args) {
        CHECK_TYPE(L"arr", args[0]);
        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        arr->PopElement();

        return ARRAY(MOVE(*arr));
        }, 1);         // get: arr

    _DEFINE_FUNCTION(L"split", [](Args_t args) {

        CHECK_TYPE(L"str", args[0]);

        StringValue* value = dynamic_cast<StringValue*>(args[0].get());

        WString str       = value->AsString();
        WString separator = args[1]->AsString();

        ArrayValue resultArray;

        size_t pos = 0;
        while ((pos = str.find(separator)) != std::wstring::npos) {

            resultArray.AddElement(STRING(str.substr(0, pos)));
            str.erase(0, pos + separator.length());

        }
        resultArray.AddElement(STRING(str));

        return ARRAY(MOVE(resultArray));
        }, 2);       // get: str, separator

    _DEFINE_FUNCTION(L"map", [](Args_t args) {

        ArrayValue resultArray;
        
        CHECK_TYPE(L"arr", args[0]);

        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        for (auto& el : *arr) {
            resultArray.AddElement(args[1]->operator()(HAND_OVER_ARGS(MOVE(el->clone()))));
        }

        return ARRAY(MOVE(resultArray));
        }, 2);         // get: arr, func

    _DEFINE_FUNCTION(L"clear", [](Args_t args) {
        return ARRAY(ArrayValue());
        }, 0);       // get: nothing

    _DEFINE_FUNCTION(L"empty", [](Args_t args) {

        CHECK_TYPE(L"arr", args[0]);

        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());

        return BOOL(arr->Empty());
        }, 1);       // get: arr

    _DEFINE_FUNCTION(L"join", [](Args_t args) {

        CHECK_TYPE(L"arr", args[0]);

        ArrayValue* arr = dynamic_cast<ArrayValue*>(args[0].get());
        WString separator = args[1]->AsString();

        WString result;

        for (auto& el : *arr) {
            result += el->AsString() + separator;
        }

        return STRING(result);
        }, 2);        // get: arr, separator
}

Funcs_t Functions::functions;