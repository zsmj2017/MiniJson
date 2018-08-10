#pragma once

#include "json.h"
#include "jsonException.h"
#include <variant>

namespace miniJson {

//Implement class:JsonValue
class JsonValue {
public:// ctor
	explicit JsonValue(nullptr_t) :_val(nullptr) {}
	explicit JsonValue(bool val) :_val(val) {}
	explicit JsonValue(double val) :_val(val) {}
	explicit JsonValue(const std::string& val):_val(val){}
	explicit JsonValue(const Json::_array& val):_val(val) {}


public:// move ctor for string,array and object
	explicit JsonValue(std::string&& val) :_val(std::move(val)) {}
	explicit JsonValue(Json::_array&& val) :_val(std::move(val)) {}

public:// dtor
	~JsonValue() = default;

public:// type interface
	JsonType getType() const;

public:// interface for array and object
	size_t size() const;

	// random_access
	const Json& operator[](size_t) const;
	Json& operator[](size_t);

public:// convert jsonValue into value instance 
	nullptr_t toNull() const;
	bool toBool() const;
	double toDouble() const;
	const std::string& toString() const;
	const Json::_array& toArray() const;

private:
	//std::varient is a C++17 features,like union in C language
	//More information can be seen in https://en.cppreference.com/w/cpp/utility/variant
	std::variant<nullptr_t, bool, double,std::string,Json::_array> _val;
};

}