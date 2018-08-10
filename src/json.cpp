#include "json.h"
#include "parse.h"
#include "jsonValue.h"


namespace miniJson {

//Json's ctor && dtor
Json::Json(nullptr_t) :_jsonValue(std::make_unique<JsonValue>(nullptr)) {}
Json::Json(bool val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(double val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(const std::string& val): _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(const _array& val): _jsonValue(std::make_unique<JsonValue>(val)) {}

Json::~Json() {}

//Json's copy constructor && copy assignment
Json::Json(const Json& rhs) {
	switch (rhs.getType()) {
	case JsonType::Null: _jsonValue = std::make_unique<JsonValue>(nullptr); break;
	case JsonType::Bool: _jsonValue = std::make_unique<JsonValue>(rhs.toBool()); break;
	case JsonType::Number: _jsonValue = std::make_unique<JsonValue>(rhs.toDouble()); break;
	case JsonType::String: _jsonValue = std::make_unique<JsonValue>(rhs.toString()); break;
	case JsonType::Array: _jsonValue = std::make_unique<JsonValue>(rhs.toArray()); break;
	//case JsonType::Object: _jsonValue = std::make_unique<JsonValue>(rhs.toObject()); break;
	}
}

void Json::swap(Json& rhs) noexcept {
	using std::swap;
	swap(_jsonValue, rhs._jsonValue);
}

Json& Json::operator=(Json& rhs) {
	//copy && swap
	Json temp(rhs);
	swap(temp);
	return *this;
}

//Json's move operation=default
Json::Json(Json&& rhs) noexcept = default;

Json & Json::operator=(Json &&rhs) noexcept = default;

// parse interface(static member function)
Json Json::parse(const std::string& content, std::string& errMsg) noexcept{
	try {
		Parser p(content);
		return p.parse();
	}
	catch (JsonException& e) {
		errMsg = e.what();
		return Json(nullptr);
	}
}

// type interface
JsonType Json::getType() const noexcept{
	return _jsonValue->getType();
}

bool Json::isNull() const noexcept{return getType() == JsonType::Null;}
bool Json::isBool() const noexcept { return getType() == JsonType::Bool; }
bool Json::isNumber() const noexcept { return getType() == JsonType::Number; }
bool Json::isString() const noexcept { return getType() == JsonType::String; }
bool Json::isArray() const noexcept{ return getType() == JsonType::Array; }

// parse interface
bool Json::toBool() const{ return _jsonValue->toBool(); }
double Json::toDouble() const { return _jsonValue->toDouble(); }
const std::string& Json::toString() const { return _jsonValue->toString(); }
const Json::_array& Json::toArray() const{ return _jsonValue->toArray(); }

size_t Json::size() const { return _jsonValue->size(); }

const Json & Json::operator[](size_t pos) const { return _jsonValue->operator[](pos); }
Json& Json::operator[](size_t pos) { return _jsonValue->operator[](pos); }

bool operator==(const Json& lhs, const Json& rhs) noexcept {
	if (lhs.getType() != rhs.getType()) 
		return false;
	switch (lhs.getType()) {
	case JsonType::Null: return true;
	case JsonType::Bool: return lhs.toBool() == rhs.toBool();
	case JsonType::Number: return lhs.toDouble() == rhs.toDouble();
	case JsonType::String: return lhs.toString() == rhs.toString();
	case JsonType::Array: return lhs.toArray() == rhs.toArray();
	//default:return
	}
}

}// namespace miniJson
