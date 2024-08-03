#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Variables.h"

#include <algorithm>

using namespace Simple;

StructValue::StructValue(const String& name, Val_map fields)
	: name(name), fields(std::move(fields)) {}

double StructValue::AsDouble() const {
	throw Simple_Error("You can't convert a structure to a number");
}

String StructValue::AsString() const {
	return name + " {\n" + [this]() {
		String result;
		for (auto& field : fields) {
			result += "    " + field.first + ": " + field.second->AsString() + "\n";
		}
		return result;
		}() + "}";
}

ValuePtr StructValue::clone() const {
	return CREATE_PTR<StructValue>(name, [this]() -> Val_map {
		Val_map clone_fields;

		for (auto& field : fields) {
			clone_fields.emplace(field.first, field.second->clone());
		}
		return clone_fields;
		}());
}

Value& StructValue::get_ref() {
	return *this;
}

void StructValue::set_ref(ValuePtr& ref) {
	if (auto structRef = dynamic_cast<StructValue*>(ref.get())) {
		name = structRef->name;
		fields = std::move(structRef->fields);
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType StructValue::GetType() const {
	return ValueType::_STRUCT;
}

String StructValue::GetTypeInString() const {
	return name;
}

ValuePtr StructValue::operator+(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be added");
}

ValuePtr StructValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be subtructed");
}

ValuePtr StructValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be multiplicated");
}

ValuePtr StructValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be divided");
}

ValuePtr StructValue::operator++() {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr StructValue::operator++(int) {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr StructValue::operator--() {
	throw Simple_Error("You can't decrement a structure");
}

ValuePtr StructValue::operator--(int) {
	throw Simple_Error("You can't decrement a structure");
}

bool StructValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

Value& StructValue::operator[](int pos) {
	throw Simple_Error("In a structure you cannot access it by index");
}

ValuePtr StructValue::power(const ValuePtr& other) const {
	throw Simple_Error("Structure cannot be raised to a power");
}

Value& StructValue::dot(const String& key) const {
	auto find_result = fields.find(key);
	if (find_result != fields.end())
		return fields.find(key)->second->get_ref();
	throw Simple_Error("Struct \"" + name + "\" does not have a member named \"" + key + "\"");
}

int StructValue::fields_count() {
	return static_cast<int>(fields.size());
}

Str_vec StructValue::fields_names() {
	Str_vec fields_names;

	for (auto& field : fields) {
		fields_names.push_back(field.first);
	}
	return fields_names;
}