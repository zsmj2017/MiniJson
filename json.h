#pragma once

#include <string>
#include <functional>

namespace json {

enum class JsonType {
	Null,
	Bool,// true/false
	Number,
	String,
	Array,
	Object 
};

class JsonValue;

class Json {
public:
	
	explicit Json(std::nullptr_t);               // null
	explicit Json(bool);                         // true/false
	explicit Json(int val) : Json(1.0 * val) {}  // number
	explicit Json(double);                       // number

	Json parse(const std::string& content, std::string& errMsg) noexcept;

	// Accesses the type of JSON value the current value instance is
	JsonType getType() const noexcept;

private:
	std::unique_ptr<JsonValue> _jsonValue;
};
}