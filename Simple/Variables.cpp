#include "Variables.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "Utils.h"

#include "Math.h"
#include "Stream.h"

using namespace Simple;

void Variables::SetAllVariables(std::unordered_map<std::string, Variable>&& variables) {

	/*for (auto& var : variables)
	{
		if (Variables::variables.find(var.first) == Variables::variables.end())
			Variables::variables[var.first] = std::move(var.second);
	}*/

	std::unordered_map<std::string, Variable> resultMap;
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

bool Variables::IsExist(const std::string& key) {
	return variables.find(key) != variables.end();
}

ValuePtr Variables::Get(const std::string& key) {
	if (!IsExist(key)) return ZERO;
	return variables.at(key).value->clone();
}

const std::unordered_map<std::string, Variable>& Variables::GetAllVariables() {
	return variables;
}

void Variables::Set(const std::string& key, Variable value) {
	bool IsIsExist = IsExist(key);
	if (IsIsExist && IsConstant(key)) throw Simple_Error("\"" + key + "\" is const");
	else if (IsIsExist) variables[key] = std::move(value);
	else variables.emplace(key, std::move(value));
}

void Variables::SetNew(const std::string& key, Variable value) {
	if (IsExist(key)) variables[key] = std::move(value);
	else variables.emplace(key, std::move(value));
}

std::unordered_map<std::string, Variable> Variables::CreateStandartVariables() {
	std::unordered_map<std::string, Variable> vars;

	//Math::InitVars();
	//Stream::InitVars();
	//vars.emplace("true",    Variable(CREATE_PTR<NumberValue>(1),   true));
	//vars.emplace("false",   Variable(CREATE_PTR<NumberValue>(0),   true));
	vars.emplace("__denys", Variable(CREATE_PTR<NumberValue>(666), false));
	return vars;
}

void Variables::PushState() {
	/*std::unordered_map<std::string, ValuePtr> currentState;
	copy_variables(Variables::GetAllVariables(), currentState);
	variablesState.push(std::move(currentState));*/

	std::unordered_map<std::string, Variable> currentState;
	copy_variables(Variables::GetAllVariables(), currentState);
	variablesState.push(std::move(currentState));
}

void Variables::PopState() {
	/*if (!variablesState.empty()) {
		Variables::SetAllVariables(std::move(variablesState.top()));
		variablesState.pop();
	}
	else {
		throw Simple_Error("No variable state to restore");
	}*/
	if (!variablesState.empty()) {
		Variables::SetAllVariables(std::move(variablesState.top()));
		variablesState.pop();
	}
	else {
		throw Simple_Error("No variable state to restore");
	}
}

bool Variables::IsConstant(const std::string& key) {
	for (auto& var : variables) {
		if (var.first == key && var.second.is_const)
			return true;
	}
	return false;
}

std::unordered_map<std::string, Variable> Variables::variables = CreateStandartVariables();

std::stack<std::unordered_map<std::string, Variable>> Variables::variablesState;