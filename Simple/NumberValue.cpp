#include "Values.h"
#include "Utils.h"
#include "Simple_Error.h"

using namespace Simple;

NumberValue::NumberValue(const double value) 
	: value(value) {}

double NumberValue::AsDouble() {
	return value;
}

std::string NumberValue::AsString() {
	int int_value = static_cast<int>(value);
	if (value == int_value)
		return std::to_string(int_value);
	return std::to_string(value);
}

ValuePtr NumberValue::clone() const {
	return NUMBER(value);
}

Value& NumberValue::get_ref() {
	return *this;
}

void NumberValue::set_ref(ValuePtr& ref) {
	if (auto numberRef = dynamic_cast<NumberValue*>(ref.get())) {
		value = numberRef->value;
	}
	else {
		throw Simple_Error("Invalid reference type");
	}
}

ValueType NumberValue::GetType() const {
	return ValueType::NUMBER;
}

std::string NumberValue::GetTypeInString() const {
	return "\"Number\"";
}

ValuePtr NumberValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return NUMBER(value + other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: " 
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator-(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return NUMBER(value - other->AsDouble());
	throw Simple_Error("- There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return NUMBER(value * other->AsDouble());
	else if (other->GetType() == ValueType::STRING) {
		auto result = [this, &other]() {
			std::string result, str = other->AsString();
			for (size_t i = 0; i < value; i++) {
				result += str;
			}
			return result;
			};
		return STRING(result());
	}
	throw Simple_Error("* There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator/(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return NUMBER(value / other->AsDouble());
	throw Simple_Error("/ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator++() {
	++value;
	return NUMBER(value);
}

ValuePtr NumberValue::operator++(int) {
	ValuePtr temp = NUMBER(value);
	++value;
	return std::move(temp);
}

ValuePtr NumberValue::operator--() {
	--value;
	return NUMBER(value);
}

ValuePtr NumberValue::operator--(int) {
	ValuePtr temp = NUMBER(value);
	--value;
	return std::move(temp);
}

bool NumberValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value < other->AsDouble();

	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value > other->AsDouble();

	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value <= other->AsDouble();

	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value >= other->AsDouble();

	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value == other->AsDouble();

	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER)
		return value != other->AsDouble();

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator[](int pos) const {
	auto num_size = [](int val) {
		if (val == 0) return 1;
		val = std::abs(val);
		return static_cast<int>(std::log10(val)) + 1;
		};

	if (pos >= num_size(static_cast<int>(value)))
		throw Simple_Error("Pos greater than number length");
	else if (pos < 0)
		throw Simple_Error("Pos cannot be negative");

	return NUMBER([num_size](int num, int index) {
		num = std::abs(num);
		int numDigits = num_size(num);

		int divisor = static_cast<int>(std::pow(10, numDigits - index - 1));
		return (num / divisor) % 10;
		}(static_cast<int>(value), pos));
}

ValuePtr NumberValue::power(const ValuePtr& other) const {
	return NUMBER(std::pow(value, other->AsDouble()));
}

ValuePtr NumberValue::dot(const std::string& key) const {
	throw Simple_Error("Number does not have a member named \"" + key + "\"");
}