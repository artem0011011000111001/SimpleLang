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
		virtual double AsDouble() = 0;
		virtual std::string AsString() = 0;

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

		virtual ValuePtr operator[](int pos) const = 0;

		virtual ValuePtr power(const ValuePtr& other) const = 0;
		virtual ValuePtr dot(const std::string& key) const = 0;

		virtual ~Value() = default;
	};

	class NumberValue : public Value {

		double value;
		ValuePtr ref;

	public:
		NumberValue(const double value);
		NumberValue() = default;

		double AsDouble() override;
		virtual std::string AsString() override;

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

		ValuePtr operator[](int pos) const override;

		ValuePtr power(const ValuePtr& other) const override;
		ValuePtr dot(const std::string& key) const override;
	};

	class StringValue : public Value {

		std::string value;
		ValuePtr ref;

	public:
		StringValue(const std::string value);
		StringValue() = default;

		double AsDouble() override;
		virtual std::string AsString() override;

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

		ValuePtr operator[](int pos) const override;

		ValuePtr power(const ValuePtr& other) const override;
		ValuePtr dot(const std::string& key) const override;
	};

	class StructValue : public Value {

		std::string name;
		std::unordered_map<std::string, ValuePtr> fields;
		ValuePtr ref = nullptr;

	public:
		StructValue(const std::string& name, std::unordered_map<std::string, ValuePtr> fields);
		StructValue() = default;

		double AsDouble() override;
		virtual std::string AsString() override;

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

		ValuePtr operator[](int pos) const override;

		ValuePtr power(const ValuePtr& other) const override;
		ValuePtr dot(const std::string& key) const override;
	};
}
#endif // _VALUES_H_