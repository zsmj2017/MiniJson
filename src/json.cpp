#include "json.h"
#include "parse.h"
#include "jsonValue.h"


namespace miniJson {

//Json's ctor
Json::Json(nullptr_t) :_jsonValue(std::make_unique<JsonValue>(nullptr)) {}
Json::Json(bool val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(double val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(const std::string &val): _jsonValue(std::make_unique<JsonValue>(val)) {}

Json::Json(const Json& rhs) {
	switch (rhs.getType()) {
	case JsonType::Null: _jsonValue = std::make_unique<JsonValue>(nullptr); break;
	case JsonType::Bool: _jsonValue = std::make_unique<JsonValue>(rhs.toBool()); break;
	case JsonType::Number: _jsonValue = std::make_unique<JsonValue>(rhs.toDouble()); break;
	case JsonType::String: _jsonValue = std::make_unique<JsonValue>(rhs.toString()); break;
	}
}

Json::Json(Json&& rhs) noexcept = default;

Json & Json::operator=(Json &&rhs) noexcept = default;

Json::~Json() {}

void Json::swap(Json& rhs) noexcept {
	using std::swap;
	swap(_jsonValue, rhs._jsonValue);
}

Json& Json::operator=(Json& rhs) {
	Json temp(rhs);
	swap(temp);
	return *this;
}

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

JsonType Json::getType() const noexcept{
	return _jsonValue->getType();
}

bool Json::isNull() const noexcept{return getType() == JsonType::Null;}
bool Json::isBool() const noexcept { return getType() == JsonType::Bool; }
bool Json::isNumber() const noexcept { return getType() == JsonType::Number; }
bool Json::isString() const noexcept { return getType() == JsonType::String; }
bool Json::toBool() const{ return _jsonValue->toBool(); }
double Json::toDouble() const{ return _jsonValue->toDouble(); }
std::string Json::toString() const { return _jsonValue->toString(); }

}// namespace miniJson
