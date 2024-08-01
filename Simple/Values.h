#pragma once

#ifndef _VALUES_H_
#define _VALUES_H_

#include "Simple_typedefs.h"
#include "Struct.h"
#include "Utils.h"

#include <string>
#include <unordered_map>

namespace Simple {

	enum class ValueType;

	class Value {

	public:
		virtual double AsDouble() const = 0;
		virtual std::string AsString() const = 0;

		virtual ValuePtr clone() const = 0;
		virtual Value& get_ref() = 0;
		virtual void set_ref(ValuePtr& ref) = 0;

		virtual ValueType GetType() const = 0;
		virtual std::string GetTypeInString() const = 0;

		virtual ValuePtr operator+(const ValuePtr& other) const = 0;
		virtual ValuePtr operator-(const ValuePtr& other) const = 0;
		virtual ValuePtr operator*(const ValuePtr& other) const = 0;
		virtual ValuePtr operator/(const ValuePtr& other) const = 0;

		virtual ValuePtr operator++() = 0;
		virtual ValuePtr operator++(int) = 0;
		virtual ValuePtr operator--() = 0;
		virtual ValuePtr operator--(int) = 0;

		virtual bool operator<(const ValuePtr& other) const = 0;
		virtual bool operator>(const ValuePtr& other) const = 0;
		virtual bool operator<=(const ValuePtr& other) const = 0;
		virtual bool operator>=(const ValuePtr& other) const = 0;
		virtual bool operator==(const ValuePtr& other) const = 0;
		virtual bool operator!=(const ValuePtr& other) const = 0;

		virtual Value& operator[](int pos) = 0;

		virtual ValuePtr power(const ValuePtr& other) const = 0;
		virtual Value& dot(const std::string& key) const = 0;

		virtual ~Value() = default;
	};

	class DigitValue : public Value {

		double value;

	public:
		DigitValue(const double value);
		DigitValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;
	};

	class NumberValue : public Value {

		double value;

	public:
		NumberValue(const double value);
		NumberValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;
	};

	class CharValue : public Value {

		std::string value;

	public:
		CharValue(const std::string& value);
		CharValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;
	};

	class StringValue : public Value {

		std::vector<CharValue> value;

	public:
		StringValue(const std::string& value);
		StringValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;
	};

	class StructValue : public Value {

		std::string name;
		Val_map fields;

	public:
		StructValue(const std::string& name, Val_map fields);
		StructValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;

		int fields_count();

		std::vector<std::string> fields_names();
	};

	class VoidValue : public Value {
	public:
		VoidValue() = default;

		double AsDouble() const override;
		std::string AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		std::string GetTypeInString() const override;

		ValuePtr operator+(const ValuePtr& other) const override;
		ValuePtr operator-(const ValuePtr& other) const override;
		ValuePtr operator*(const ValuePtr& other) const override;
		ValuePtr operator/(const ValuePtr& other) const override;

		ValuePtr operator++() override;
		ValuePtr operator++(int) override;
		ValuePtr operator--() override;
		ValuePtr operator--(int) override;

		bool operator<(const ValuePtr& other) const override;
		bool operator>(const ValuePtr& other) const override;
		bool operator<=(const ValuePtr& other) const override;
		bool operator>=(const ValuePtr& other) const override;
		bool operator==(const ValuePtr& other) const override;
		bool operator!=(const ValuePtr& other) const override;

		Value& operator[](int pos) override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const std::string& key) const override;
	};
}
#endif // _VALUES_H_