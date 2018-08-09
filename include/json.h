#pragma once

#include <string>
#include <memory>

namespace miniJson {

enum class JsonType {
	Null,
	Bool,
	Number,
	String,
	Array,
	Object 
};

// PIMPL
// forward declaration for std::unique_ptr
class JsonValue;

class Json {
public:// ctor
	explicit Json(std::nullptr_t);
	explicit Json(bool);
	// convert int into double
	explicit Json(int val) : Json(1.0 * val) {}
	explicit Json(double);
	// string (without this ctor, Json("xx") will call Json(bool)
	explicit Json(const char* cstr) : Json(std::string(cstr)) {}
	explicit Json(const std::string&);

public:// dtor
	~Json();

public:// copy constructor && assignment
	Json(const Json&);
	Json& operator=(Json&);

public:// move constructor && assignment
	Json(Json&&) noexcept;
	Json& operator=(Json&&) noexcept;

public:// static interfcae
	// errMsg can store exception message(all exception will be catched)
	static Json parse(const std::string& content, std::string& errMsg) noexcept;
public:// type interface
	JsonType getType() const noexcept;
	bool isNull() const noexcept;
	bool isBool() const noexcept;
	bool isNumber() const noexcept;
	bool isString() const noexcept;

public:// convert json object into value
	bool toBool() const;
	double toDouble() const;
	std::string toString() const;

private:
	void swap(Json&) noexcept;// make copy && swap
	std::unique_ptr<JsonValue> _jsonValue;
};

}//namespace json