#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Variables.h"
#include "Method_info.h"
#include "Functions.h"
#include "ArgParams.h"

#include <algorithm>

using namespace Simple;

ClassValue::ClassValue(const WString& name, Fields_t fields, Methods_t methods)
	: name(name), fields(MOVE(fields)), methods(MOVE(methods)) {}

ClassValue::ClassValue(const WString& name, Fields_t fields, RawMethod_decl_t methods)
	: name(name), fields(MOVE(fields)) {

	// Solution for clearing memory from the body
	// Vec<StatementPtr> bodies;
	int i = 0;

	for (auto& method : methods) {

		MethodParams method_params;

		if (method.first == L"constructor") continue;

		for (auto& method_info : method.second) {

			bodies.push_back(MOVE(method_info.second.body));

			method_params.func_bodies.emplace(method_info.first, Functions::CreateDynamicFunction(Statement_to_method(
				bodies[i],
				method_info.second.args_params,
				method_info.second.is_any_args
			)));
			++i;

			method_params.isPrivate = method_info.second.isPrivate;
		}

		this->methods[method.first] = MOVE(method_params);
	}
}

double ClassValue::AsDouble() const {
	return call_method(L"to_num", 0, {})->AsDouble();
}

WString ClassValue::AsString() const {
	return call_method(L"to_str", 0, {})->AsString();
}

ValuePtr ClassValue::clone() const {
	return CREATE_PTR<ClassValue>(name, copy_vars(fields), copy_methods(methods));
}

Value& ClassValue::get_ref() {
	return *this;
}

void ClassValue::set_ref(ValuePtr& ref) {
	if (auto classRef = dynamic_cast<ClassValue*>(ref.get())) {
		name = classRef->name;

		fields  = MOVE(classRef->fields);
		methods = MOVE(classRef->methods);
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType ClassValue::GetType() const {
	return ValueType::_CLASS;
}

WString ClassValue::GetTypeInString() const {
	return name;
}

Simple_Iterator ClassValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator ClassValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr ClassValue::operator+(const ValuePtr& other) const {
	return nullptr;
	//return call_method(L"add", 1, _HAND_OVER_ARGS(other));
}

ValuePtr ClassValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be subtructed");
}

ValuePtr ClassValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be multiplicated");
}

ValuePtr ClassValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be divided");
}

void ClassValue::operator+=(const ValuePtr& other) {
	throw Simple_Error("Structures cannot be added");
}

void ClassValue::operator-=(const ValuePtr& other) {
	throw Simple_Error("Structures cannot be subtructed");
}

void ClassValue::operator*=(const ValuePtr& other) {
	throw Simple_Error("Structures cannot be multiplicated");
}

void ClassValue::operator/=(const ValuePtr& other) {
	throw Simple_Error("Structures cannot be divided");
}

void ClassValue::powereq(const ValuePtr& other) {
	throw Simple_Error("Structure cannot be raised to a power");
}

ValuePtr ClassValue::operator++() {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr ClassValue::operator++(int) {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr ClassValue::operator--() {
	throw Simple_Error("You can't decrement a structure");
}

ValuePtr ClassValue::operator--(int) {
	throw Simple_Error("You can't decrement a structure");
}

bool ClassValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool ClassValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool ClassValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool ClassValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool ClassValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool ClassValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

Value& ClassValue::operator[](int pos) {
	throw Simple_Error("In a structure you cannot access it by index");
}

ValuePtr ClassValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr ClassValue::power(const ValuePtr& other) const {
	throw Simple_Error("Structure cannot be raised to a power");
}

Value& ClassValue::dot(const WString& key) const {

	auto find_result = fields.find(key);
	if (find_result != fields.end()) {

		if (find_result->second.is_const) {
			cloneValue = find_result->second.value->clone();
			return cloneValue->get_ref();
		}

		else return find_result->second.value->get_ref();
	}
	throw Simple_Error(L"Class \"" + name + L"\" does not have a member named \"" + key + L"\"");
}

int ClassValue::fields_count() {
	return static_cast<int>(fields.size());
}

WStr_vec ClassValue::fields_names() {
	WStr_vec fields_names;

	for (auto& field : fields) {
		fields_names.push_back(field.first);
	}
	return fields_names;
}   

std::function<VALUE(Args_t)> ClassValue::Statement_to_method(StatementPtr& statement, ArgsParams_t& args_params, bool is_any_args) {

	return [this, &statement, &args_params, is_any_args](Args_t args) -> VALUE {
		ValuePtr return_value = VOID;

		try {
			Variables::PushState();

			create_arguments(args_params, args, is_any_args);


			Variables::SetNew(L"this", Variable(CLASS(name, copy_vars(fields), copy_methods(methods))));
			
			bodies;

			statement->execute();
		}
		catch (ReturnStatement::ReturnValue& ReturnValue) {
			return_value = MOVE(ReturnValue.value);
		}

		ClassValue* value_this = dynamic_cast<ClassValue*>(Variables::Get(L"this").get());

		if (!value_this)
			throw Simple_Error("Assignment for this by another type");

		*this = MOVE(*dynamic_cast<ClassValue*>(Variables::Get(L"this").get()));

		disassemble_arguments();
		Variables::PopState();

		return MOVE(return_value);
		};
}

bool ClassValue::exist(const WString& key) const {
	return methods.find(key) != methods.end();
}

bool ClassValue::exist_overload(const FuncParams& func, int args_count) const {
	return func.func_bodies.find(args_count) != func.func_bodies.end();
}

FuncParams ClassValue::get_method(const WString& key) const {
	if (exist(key)) {
		return methods.find(key)->second.clone();
	}
}

ValuePtr ClassValue::call_method(const WString& key, int args_count, Args_t args) const {
	auto method = get_method(key);

	if (exist_overload(method, args_count))
		return method.func_bodies.find(args_count)->second->execute(MOVE(args));
}