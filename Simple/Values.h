#pragma once

#ifndef _VALUES_H_
#define _VALUES_H_

#include "Simple_typedefs.h"
#include "Utils.h"

#include <string>

namespace Simple {

	class Value {

	public:
		virtual double AsDouble() = 0;
		virtual std::string AsString() = 0;

		virtual ValuePtr clone() const = 0;

		virtual ValueType GetType() const = 0;

		virtual bool operator==(const ValuePtr& other) const = 0;

		virtual ~Value() = default;
	};

	class NumberValue : public Value {

		double value;

	public:
		NumberValue(const double value);
		NumberValue() = default;

		double AsDouble() override;
		virtual std::string AsString() override;

		ValuePtr clone() const override;

		ValueType GetType() const override;

		bool operator==(const ValuePtr& other) const override;
	};

	class StringValue : public Value {

		std::string value;

	public:
		StringValue(const std::string value);
		StringValue() = default;

		double AsDouble() override;
		virtual std::string AsString() override;

		ValuePtr clone() const override;

		ValueType GetType() const override;

		bool operator==(const ValuePtr& other) const override;
	};
}
#endif // !_VALUES_H_