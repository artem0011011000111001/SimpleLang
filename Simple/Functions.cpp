#include "Functions.h"
#include "Function.h"
#include "Values.h"
#include "Simple_Error.h"

#include <iostream>

using namespace Simple;

bool Functions::IsExist(const String& key) {
	return functions.find(key) != functions.end();
}

FunctionPtr Functions::Get(const String& key) {
	if (!IsExist(key)) throw Simple_Error("Function \"" + key + "\" not defined");
	return std::move(functions.at(key)->clone());
}

void Functions::Set(const String& key, FunctionPtr value) {
	if (IsExist(key)) throw Simple_Error("\"" + key + "\" is already defined");
	else functions.emplace(key, std::move(value));
}

void Functions::RegisterDynamicFunction(const String& name, std::function<VALUE(Args_t)> funcbody, const size_t argscount) {
    class DynamicFunction : public Function {
        std::function<ValuePtr(std::vector<ValuePtr>)> funcbody;
        size_t argscount;
    public:
        DynamicFunction(std::function<VALUE(Args_t)> func, const size_t argscount)
            : funcbody(std::move(func)), argscount(argscount) {}

        ValuePtr execute(Args_t args) override {
            size_t param_count = args.size();
            if (argscount != any_args)
                if (param_count != argscount) {
                    throw Simple_Error("Expected " + std::to_string(argscount) + " arg(s) instead of " + std::to_string(param_count));
                }
            return funcbody(std::move(args));
        }

        FunctionPtr clone() const override {
            return CREATE_PTR<DynamicFunction>(funcbody, argscount);
        }
    };

    Set(name, CREATE_PTR<DynamicFunction>(funcbody, argscount));
}

void Functions::CreateStandartFunctions() {
    _DEFINE_FUNCTION("print", [](std::vector<ValuePtr> args) {
        for (auto& arg : args) {
            std::cout << arg->AsString();
        }
        return ZERO;
    });

    _DEFINE_FUNCTION("println", [](std::vector<ValuePtr> args) {
        for (auto& arg : args) {
            std::cout << arg->AsString() << std::endl;
        }
        return ZERO;
        });
}

Funcs_t Functions::functions;