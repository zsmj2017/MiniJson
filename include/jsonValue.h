#pragma once

#include "json.h"
#include "jsonException.h"
#include <variant>

namespace miniJson {

class JsonValue {
public:// ctor
	explicit JsonValue(nullptr_t val) :_val(val) {}
	explicit JsonValue(bool val) :_val(val) {}
	explicit JsonValue(double val) :_val(val) {}
	explicit JsonValue(const std::string& val):_val(val){}
	explicit JsonValue(std::string&& val) :_val(std::move(val)) {}

public:// dtor
	~JsonValue() = default;

public:// type interface
	JsonType getType() const;

public:// convert jsonValue into value instance 
	nullptr_t toNull() const;
	bool toBool() const;
	double toDouble() const;
	std::string toString() const;

private:
	//std::varient is a C++17 features,like union in C language
	//More information can be seen in https://en.cppreference.com/w/cpp/utility/variant
	std::variant<nullptr_t, bool, double,std::string> _val;
};

}