#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

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
public:// alias declarations
	using _array = std::vector<Json>;
	using _object = std::unordered_map<std::string, Json>;

public:// ctor
	explicit Json(std::nullptr_t);
	explicit Json(bool);
	// convert int into double
	explicit Json(int val) : Json(1.0 * val) {}
	explicit Json(double);
	// string (without this ctor, Json("xx") will call Json(bool)
	explicit Json(const char* cstr) : Json(std::string(cstr)) {}
	explicit Json(const std::string&);
	explicit Json(const _array&);
	explicit Json(const _object&);

public:// dtor
	~Json();

public:// copy constructor && assignment
	Json(const Json&);// deeply copy
	Json& operator=(Json&) noexcept; // copy && swap

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
	bool isArray() const noexcept;
	bool isObject() const noexcept;

public:// convert json object into value
	bool toBool() const;
	double toDouble() const;
	const std::string& toString() const;
	const _array& toArray() const;
	const _object& toObject() const;

public:// interface for array && object
	size_t size() const;
	// operator[] for array
	Json& operator[](size_t);
	const Json& operator[](size_t) const;
	// operator[] for object
	Json& operator[](const std::string&);
	const Json& operator[](const std::string&) const;

private:
	void swap(Json&) noexcept;// make copy && swap
	std::unique_ptr<JsonValue> _jsonValue;
};

bool operator==(const Json&, const Json&) noexcept;
inline bool operator!=(const Json& lhs, const Json& rhs) noexcept {return !(lhs == rhs);}

}//namespace miniJson