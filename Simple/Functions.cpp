#include "Functions.h"
#include "Function.h"
#include "Values.h"
#include "Simple_Error.h"

#include <iostream>

using namespace Simple;

bool Functions::IsExist(const std::string& key) {
	return functions.find(key) != functions.end();
}

FunctionPtr Functions::Get(const std::string& key) {
	if (!IsExist(key)) throw Simple_Error("Function \"" + key + "\" not defined");
	return std::move(functions.at(key)->clone());
}

Function& Functions::GetRef(const std::string& key) {
    if (!IsExist(key)) throw Simple_Error("Function \"" + key + "\" not defined");
    return functions.at(key)->get_ref();
}

void Functions::Set(const std::string& key, FunctionPtr value) {
	if (IsExist(key)) throw Simple_Error("\"" + key + "\" is already defined");
	else functions.emplace(key, std::move(value));
}

void Functions::RegisterDynamicFunction(const std::string& name, std::function<VALUE(Args_t)> funcbody, const size_t argscount) {
    class DynamicFunction : public Function {
        std::function<ValuePtr(std::vector<ValuePtr>)> funcbody;
        size_t argscount;
    public:
        DynamicFunction(std::function<ValuePtr(std::vector<ValuePtr>)> func, const size_t argscount)
            : funcbody(std::move(func)), argscount(argscount) {}

        ValuePtr execute(std::vector<ValuePtr> args) override {
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

        Function& get_ref() override {
            return *this;
        }

        void set_ref(FunctionPtr& ref) override {
            if (auto castRef = dynamic_cast<DynamicFunction*>(ref.get())) {
                funcbody = std::move(castRef->funcbody);
                argscount = castRef->argscount;
            }
            else {

                throw Simple_Error("Invalid reference type");
            }
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

std::unordered_map<std::string, FunctionPtr> Functions::functions;