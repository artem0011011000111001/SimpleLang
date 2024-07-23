#include "Functions.h"
#include "Function.h"
#include "Values.h"
#include "Simple_Error.h"

#include "Math.h"
#include "Stream.h"
#include "Type.h"

#include <iostream>

using namespace Simple;

bool Functions::IsExist(const std::string& key) {
	return functions.find(key) != functions.end();
}

FunctionPtr Functions::Get(const std::string& key) {
	if (!IsExist(key)) throw Simple_Error("Function \"" + key + "\" not defined");
	return std::move(functions.at(key)->clone());
}

void Functions::Set(const std::string& key, FunctionPtr value) {
	if (IsExist(key)) throw Simple_Error("\"" + key + "\" is already defined");
	else functions.emplace(key, std::move(value));
}

void Functions::RegisterDynamicFunction(const std::string& name, std::function<ValuePtr(std::vector<ValuePtr>)> funcbody, const std::vector<size_t>& argscount) {
    class DynamicFunction : public Function {
    public:
        DynamicFunction(std::function<ValuePtr(std::vector<ValuePtr>)> func, std::vector<size_t> argscount)
            : funcbody(std::move(func)), argscount(std::move(argscount)) {}

        ValuePtr execute(std::vector<ValuePtr> args) override {
            size_t param_count = args.size();
            for (auto& count : argscount) {
                if (param_count != count) {
                    throw Simple_Error("Expected " + std::to_string(count) + " arg(s) instead of " + std::to_string(param_count));
                }
            }
            return funcbody(std::move(args));
        }

        FunctionPtr clone() const override {
            return CREATE_PTR<DynamicFunction>(funcbody, argscount);
        }

    private:
        std::function<ValuePtr(std::vector<ValuePtr>)> funcbody;
        std::vector<size_t> argscount;
    };

    Set(name, CREATE_PTR<DynamicFunction>(funcbody, argscount));
}

std::unordered_map<std::string, FunctionPtr> Functions::CreateStandartFunctions() {
	std::unordered_map<std::string, FunctionPtr> funcs;

    _DEFINE_FUNCTION_CLASS(PrintFunc, [](std::vector<ValuePtr> args) {
        for (auto& arg : args) {
            std::cout << arg->AsString();
        }
        return ZERO;
    }, any_args);

    _DEFINE_FUNCTION_CLASS(PrintlnFunc, [](std::vector<ValuePtr> args) {
        for (auto& arg : args) {
            std::cout << arg->AsString() << std::endl;
        }
        return ZERO;
        }, any_args);

    funcs.emplace("print", CREATE_PTR<PrintFunc>());
    funcs.emplace("println", CREATE_PTR<PrintlnFunc>());
	return funcs;
}

std::unordered_map<std::string, FunctionPtr> Functions::functions = CreateStandartFunctions();
