#pragma once

#include "json.h"
#include "jsonException.h"
#include <variant>

namespace json {
class JsonValue {
public:
	explicit JsonValue(nullptr_t val) :_val(val) {}
	explicit JsonValue(bool val) :_val(val) {}
	explicit JsonValue(double val) :_val(val) {}
	~JsonValue() = default;
	JsonType getType() const;
	nullptr_t toNull() const;
	bool toBool() const;
	double toDouble() const;
private:
	std::variant<nullptr_t, bool, double> _val;
};
}