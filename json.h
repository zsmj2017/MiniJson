#pragma once

#include <string>
#include <memory>

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
	explicit Json(double);
	Json(const Json&);
	Json(Json&&) noexcept;
	~Json();
	Json& operator=(Json);

	static Json parse(const std::string& content, std::string& errMsg) noexcept;

	JsonType getType() const noexcept;

	bool isNull() const noexcept;
	bool isBool() const noexcept;
	bool isNumber() const noexcept;

	bool toBool() const;
	double toDouble() const;

private:
	void swap(Json&) noexcept;
	std::unique_ptr<JsonValue> _jsonValue;
};
}