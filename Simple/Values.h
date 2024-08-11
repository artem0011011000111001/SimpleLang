#pragma once

#ifndef _VALUES_H_
#define _VALUES_H_

#include "FuncParams.h"
#include "Simple_typedefs.h"
#include "Struct.h"
#include "Utils.h"
#include "Simple_iterator.h"

#include <string>
#include <unordered_map>

namespace Simple {

	struct FuncParams;

	enum class ValueType;

	class Simple_Iterator;

	class Value {

	public:
		virtual double AsDouble() const = 0;
		virtual WString AsString() const = 0;

		virtual ValuePtr clone() const = 0;
		virtual Value& get_ref() = 0;
		virtual void set_ref(ValuePtr& ref) = 0;

		virtual ValueType GetType() const = 0;
		virtual WString GetTypeInString() const = 0;

		virtual Simple_Iterator begin() = 0;
		virtual Simple_Iterator end() = 0;

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
		virtual ValuePtr operator()(Args_t args) const = 0;

		virtual ValuePtr power(const ValuePtr& other) const = 0;
		virtual Value& dot(const WString& key) const = 0;

		virtual ~Value() = default;
	};

	class DigitValue : public Value {

		double value;

	public:
		DigitValue(const double value);
		DigitValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};

	class NumberValue : public Value {

		double value;

	public:
		NumberValue(const double value);
		NumberValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};

	class CharValue : public Value {

		WString value;

	public:
		CharValue(const WString& value);
		CharValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};

	class StringValue : public Value {

		Vec<CharValue> value;

	public:
		StringValue(const WString& value);
		StringValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};

	class StructValue : public Value {

		WString name;
		Vars_t fields;
		mutable ValuePtr cloneValue;

	public:
		StructValue(const WString& name, Vars_t fields);
		StructValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;

		int fields_count();
		WStr_vec fields_names();
	};

	class VoidValue : public Value {
	public:
		VoidValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};

	class ArrayValue : public Value {
		
		Elements_t elements;
		mutable ValuePtr sizeRef;

	public:
		ArrayValue(Elements_t elements);
		ArrayValue() = default;

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;

		void AddElement(ValuePtr el);

		void PopElement();

		void Push_pos(ValuePtr el, int pos);

		void Pop_pos(int pos);

		bool Empty();
	};

	class FunctionValue : public Value {

		FuncParams func;

	public:
		FunctionValue(WString& key);
		FunctionValue(FuncParams func);

		double AsDouble() const override;
		WString AsString() const override;

		ValuePtr clone() const override;
		Value& get_ref() override;
		void set_ref(ValuePtr& ref) override;

		ValueType GetType() const override;
		WString GetTypeInString() const override;

		Simple_Iterator begin() override;
		Simple_Iterator end() override;

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
		ValuePtr operator()(Args_t args) const override;

		ValuePtr power(const ValuePtr& other) const override;
		Value& dot(const WString& key) const override;
	};
}
#endif // _VALUES_H_