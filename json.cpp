#include "json.h"
#include "parse.h"
#include "jsonValue.h"

namespace json {
Json::Json(nullptr_t) :_jsonValue(std::make_unique<JsonValue>(nullptr)) {}
Json::Json(bool val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
Json::Json(double val) : _jsonValue(std::make_unique<JsonValue>(val)) {}

Json::Json(const Json& rhs) {
	switch (rhs.getType()) {
	case JsonType::Null: _jsonValue = std::make_unique<JsonValue>(nullptr); break;
	case JsonType::Bool: _jsonValue = std::make_unique<JsonValue>(rhs.toBool()); break;
	case JsonType::Number: _jsonValue = std::make_unique<JsonValue>(rhs.toDouble()); break;
	}
}

Json::Json(Json&& rhs) noexcept : _jsonValue(std::move(rhs._jsonValue)) { rhs._jsonValue = nullptr; }

Json::~Json() {}

void Json::swap(Json& rhs) noexcept {
	using std::swap;
	swap(_jsonValue, rhs._jsonValue);
}

Json& Json::operator=(Json rhs) {
	swap(rhs);
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
bool Json::toBool() const{ return _jsonValue->toBool(); }
double Json::toDouble() const{ return _jsonValue->toDouble(); }
}
