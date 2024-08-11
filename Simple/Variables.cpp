#include "Variables.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "Utils.h"

using namespace Simple;

void Variables::SetAllVariables(Vars_t&& variables) {

	/*for (auto& var : variables)
	{
		if (Variables::variables.find(var.first) == Variables::variables.end())
			Variables::variables[var.first] = std::move(var.second);
	}*/

	Vars_t resultMap;
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

bool Variables::IsExist(const WString& key) {
	return variables.find(key) != variables.end();
}

ValuePtr Variables::Get(const WString& key) {
	if (!IsExist(key)) return ZERO;
	return variables.at(key).value->clone();
}

Value& Variables::GetRef(const WString& key) {
	if (!IsExist(key)) throw Simple_Error(L"\"" + key + L"\" not defined");
	return variables.at(key).value->get_ref();
}

const Vars_t& Variables::GetAllVariables() {
	return variables;
}

void Variables::Set(const WString& key, Variable value) {
	auto CheckInvalidName = [key](WString invalidName) {
		if (key == invalidName)
			throw Simple_Error(L"\"" + invalidName + L"\" invalid name");
		};

	CheckInvalidName(L"true");	////
	CheckInvalidName(L"false");
	CheckInvalidName(L"void");
	CheckInvalidName(L"this");

	bool IsIsExist = IsExist(key);
	if (IsIsExist && IsConstant(key)) throw Simple_Error(L"\"" + key + L"\" is const");
	else if (IsIsExist) variables[key] = MOVE(value);
	else variables.emplace(key, MOVE(value));
}

void Variables::SetNew(const WString& key, Variable value) {
	if (IsExist(key)) variables[key] = MOVE(value);
	else variables.emplace(key, MOVE(value));
}

Vars_t Variables::CreateStandartVariables() {
	Vars_t vars;

	//Math::InitVars();
	//Stream::InitVars();
	//vars.emplace("true",    Variable(CREATE_PTR<NumberValue>(1),   true));
	//vars.emplace("false",   Variable(CREATE_PTR<NumberValue>(0),   true));
	vars.emplace(L"__denys", Variable(NUMBER(666), false));
	return vars;
}

void Variables::PushState() {
	/*std::unordered_map<WString, ValuePtr> currentState;
	copy_variables(Variables::GetAllVariables(), currentState);
	variablesState.push(std::move(currentState));*/

	Vars_t currentState;
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
	if (!StateEmpty()) {
		Variables::SetAllVariables(std::move(variablesState.top()));
		variablesState.pop();
	}
	else {
		throw Simple_Error("No variable state to restore");
	}
}

bool Variables::StateEmpty() {
	return variablesState.empty();
}

bool Variables::IsConstant(const WString& key) {
	for (auto& var : variables) {
		if (var.first == key && var.second.is_const)
			return true;
	}
	return false;
}

Vars_t Variables::variables = CreateStandartVariables();

std::stack<Vars_t> Variables::variablesState;