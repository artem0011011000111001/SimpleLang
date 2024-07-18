#include "Variables.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"

#include "Math.h"
#include "Stream.h"

using namespace Simple;

void Variables::SetAllVariables(std::unordered_map<std::string, ValuePtr>&& variables) {

	/*for (auto& var : variables)
	{
		if (Variables::variables.find(var.first) == Variables::variables.end())
			Variables::variables[var.first] = std::move(var.second);
	}*/

	std::unordered_map<std::string, ValuePtr> resultMap;
	for (auto& pair : variables) {
		if (Variables::variables.find(pair.first) != Variables::variables.end()) {
			resultMap[pair.first] = std::move(Variables::variables[pair.first]);
		}
		else {
			resultMap.operator[](pair.first) = std::move(pair.second);
		}
	}
	Variables::variables = std::move(resultMap);
}

void Variables::SetAllConstants(const std::vector<std::string>& constants) {
	Variables::constants = constants;
}

bool Variables::IsExist(const std::string& key) {
	return variables.find(key) != variables.end();
}

ValuePtr Variables::Get(const std::string& key) {
	if (!IsExist(key)) return ZERO;
	return variables.at(key)->clone();
}

const std::unordered_map<std::string, ValuePtr>& Variables::GetAllVariables() {
	return variables;
}

const std::vector<std::string>& Variables::GetAllConstants() {
	return constants;
}

void Variables::Set(const std::string& key, ValuePtr value) {
	bool IsIsExist = IsExist(key);
	if (IsIsExist && IsConstant(key)) throw Simple_Error("\"" + key + "\" is const");
	else if (IsIsExist) variables[key] = std::move(value);
	else variables.emplace(key, std::move(value));
}

void Variables::AddConstant(const std::string& key) {
	if (!IsConstant(key)) constants.push_back(key);
}

void Simple::Variables::RemoveConstant(const std::string& key) {
	if (IsConstant(key)) constants.erase(std::find(constants.begin(), constants.end(), key));
	else throw Simple_Error("\"" + key + "\" exist already");
}

std::unordered_map<std::string, ValuePtr> Variables::CreateStandartVariables() {
	std::unordered_map<std::string, ValuePtr> vars;

	//Math::InitVars();
	//Stream::InitVars();
	vars.emplace("true",    std::make_unique<NumberValue>(1));
	vars.emplace("false",   std::make_unique<NumberValue>(0));
	vars.emplace("__denys", std::make_unique<NumberValue>(666));
	return vars;
}

void Variables::PushState() {
	/*std::unordered_map<std::string, ValuePtr> currentState;
	copy_variables(Variables::GetAllVariables(), currentState);
	variablesState.push(std::move(currentState));*/

	std::unordered_map<std::string, ValuePtr> currentState;
	copy_variables(Variables::GetAllVariables(), currentState);
	variablesState.push(std::move(currentState));

	std::vector<std::string> currentConstants = Variables::constants;
	constantsState.push(std::move(currentConstants));
}

void Variables::PopState() {
	/*if (!variablesState.empty()) {
		Variables::SetAllVariables(std::move(variablesState.top()));
		variablesState.pop();
	}
	else {
		throw Simple_Error("No variable state to restore");
	}*/
	if (!variablesState.empty() && !constantsState.empty()) {
		Variables::SetAllVariables(std::move(variablesState.top()));
		variablesState.pop();

		Variables::SetAllConstants(std::move(constantsState.top()));
		constantsState.pop();
	}
	else {
		throw Simple_Error("No variable state to restore");
	}
}

bool Variables::IsConstant(const std::string& key) {
	for (const auto& constant : constants) {
		if (key == constant) return true;
	}
	return false;
}

std::unordered_map<std::string, ValuePtr> Variables::variables = CreateStandartVariables();

std::vector<std::string> Variables::constants = {
	"true",
	"false",
	"endl",
	"PI",
	"E"
};

std::stack<std::unordered_map<std::string, ValuePtr>> Variables::variablesState;
std::stack<std::vector<std::string>> Variables::constantsState;