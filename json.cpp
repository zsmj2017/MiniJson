#include "json.h"
#include "jsonValue.h"
#include "parse.h"

namespace json {
	Json::Json(nullptr_t) :_jsonValue(std::make_unique<JsonValue>(nullptr)) {}
	Json::Json(bool val) : _jsonValue(std::make_unique<JsonValue>(val)) {}
	Json::Json(double val) : _jsonValue(std::make_unique<JsonValue>(val)) {}

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

}
