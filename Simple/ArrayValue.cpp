#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

ArrayValue::ArrayValue(Elements_t elements)
	: elements(MOVE(elements)) {}

double ArrayValue::AsDouble() const {
	throw Simple_Error("to_num There is no operator corresponding");
}

WString ArrayValue::AsString() const {
	WString result;

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

WString ArrayValue::GetTypeInString() const {
	return L"arr";
}

Simple_Iterator ArrayValue::begin() {
	return Simple_Iterator(elements.data());
}

Simple_Iterator ArrayValue::end() {
	return Simple_Iterator(elements.data() + elements.size());
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
	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
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
	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
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
	throw Simple_Error(L"< There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool ArrayValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() > dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error(L"> There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool ArrayValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() <= dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error(L"<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool ArrayValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_ARRAY) {
		return elements.size() >= dynamic_cast<ArrayValue*>(other.get())->elements.size();
	}
	throw Simple_Error(L">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
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
	throw Simple_Error(L"== There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
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
	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& ArrayValue::operator[](int pos) {
	check_pos(pos, (int)elements.size(), "arr");
	return elements[pos]->get_ref();
}

ValuePtr ArrayValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr ArrayValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& ArrayValue::dot(const WString& key) const {
	if (key == L"size") return *(sizeRef = NUMBER((double)elements.size()));
	throw Simple_Error(L"Array does not have a member named \"" + key + L"\"");
}

void ArrayValue::AddElement(ValuePtr el) {
	elements.push_back(MOVE(el));
}

void ArrayValue::PopElement() {
	if (elements.size())
		elements.pop_back();
}

void ArrayValue::Push_pos(ValuePtr el, int pos) {
	check_pos(pos, (int)elements.size(), "array size");

	elements.emplace(elements.begin() + pos, MOVE(el));
}

void ArrayValue::Pop_pos(int pos) {
	check_pos(pos, (int)elements.size(), "array size");

	elements.erase(elements.begin() + pos);
}

bool ArrayValue::Empty() {
	return elements.empty();
}
