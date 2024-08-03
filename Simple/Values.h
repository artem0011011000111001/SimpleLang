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
		virtual String AsString() const = 0;

		virtual ValuePtr clone() const = 0;
		virtual Value& get_ref() = 0;
		virtual void set_ref(ValuePtr& ref) = 0;

		virtual ValueType GetType() const = 0;
		virtual String GetTypeInString() const = 0;

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
		virtual Value& dot(const String& key) const = 0;

		virtual ~Value() = default;
	};

	class DigitValue : public Value {

		double value;

	public:
		DigitValue(const double value);
		DigitValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;
	};

	class NumberValue : public Value {

		double value;

	public:
		NumberValue(const double value);
		NumberValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;
	};

	class CharValue : public Value {

		String value;

	public:
		CharValue(const String& value);
		CharValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;
	};

	class StringValue : public Value {

		std::vector<CharValue> value;

	public:
		StringValue(const String& value);
		StringValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;
	};

	class StructValue : public Value {

		String name;
		Val_map fields;

	public:
		StructValue(const String& name, Val_map fields);
		StructValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;

		int fields_count();
		Str_vec fields_names();
	};

	class VoidValue : public Value {
	public:
		VoidValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;
	};

	class ArrayValue : public Value {
		
		Elements_t elements;
		mutable ValuePtr sizeRef;

	public:
		ArrayValue(Elements_t elements);
		ArrayValue() = default;

		double AsDouble() const override;
		String AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		String GetTypeInString() const override;

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
		Value& dot(const String& key) const override;

		void AddElement(ValuePtr el);
	};
}
#endif // _VALUES_H_