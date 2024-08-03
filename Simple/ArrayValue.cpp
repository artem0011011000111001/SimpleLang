#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

ArrayValue::ArrayValue(Elements_t elements)
	: elements(MOVE(elements)) {}

double ArrayValue::AsDouble() const {
	throw Simple_Error("to_num There is no operator corresponding");
}

String ArrayValue::AsString() const {
	String result;

	for (auto& el : elements) {
		result += el->AsString();
	}
	return result;
}

ValuePtr ArrayValue::clone() const {
	Elements_t copy_elements;

	for (auto& el : elements) {
		copy_elements.push_back(MOVE(el->clone()));
	}
	return ARRAY(MOVE(copy_elements));
}

Value& ArrayValue::get_ref() {
	return *this;
}

void ArrayValue::set_ref(ValuePtr& ref) {
	if (auto arrayRef = dynamic_cast<ArrayValue*>(ref.get())) {
		for (auto& el : arrayRef->elements) {
			elements.push_back(MOVE(el->clone()));
		}
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType ArrayValue::GetType() const {
	return ValueType::_ARRAY;
}

String ArrayValue::GetTypeInString() const {
	return "arr";
}

ValuePtr ArrayValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return ARRAY(MOVE([this, &other]() {
			ArrayValue final_array;
			final_array.set_ref((ValuePtr&)*this);

			auto other_array = dynamic_cast<ArrayValue*>(other.get());
			for (auto& el : other_array->elements) {
				final_array.AddElement(MOVE(el->clone()));
			}
			return final_array;
			}()));
	}
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr ArrayValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("+ There is no operator corresponding");
}

ValuePtr ArrayValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_) {
		ArrayValue final_array;
		for (size_t i = 0, count = (int)other->AsDouble(); i < count; i++) {
			for (auto& el : elements) {
				final_array.AddElement(MOVE(el->clone()));
			}
		}
		return ARRAY(MOVE(final_array));
	}
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr ArrayValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

ValuePtr ArrayValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr ArrayValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr ArrayValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr ArrayValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool ArrayValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() < dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool ArrayValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() > dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool ArrayValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() <= dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool ArrayValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() >= dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool ArrayValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		auto other_array = dynamic_cast<ArrayValue*>(other.get());
		auto other_elements_it = other_array->elements.begin();
		for (auto& el : elements) {
			if (el->operator!=(*other_elements_it))
				return false;
			++other_elements_it;
		}
		return true;
	}
	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool ArrayValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		auto other_array = dynamic_cast<ArrayValue*>(other.get());
		auto other_elements_it = other_array->elements.begin();
		for (auto& el : elements) {
			if (el->operator!=(*other_elements_it))
				return true;
			++other_elements_it;
		}
		return false;
	}
	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

Value& ArrayValue::operator[](int pos) {
	check_pos(pos, (int)elements.size(), "arr");
	return elements[pos]->get_ref();
}

ValuePtr ArrayValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& ArrayValue::dot(const String& key) const {
	if (key == "size") return *(sizeRef = NUMBER((double)elements.size()));
	throw Simple_Error("Array does not have a member named \"" + key + "\"");
}

void ArrayValue::AddElement(ValuePtr el) {
	elements.push_back(MOVE(el));
}