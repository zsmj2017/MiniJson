#include "jsonValue.h"
#include "jsonException.h"

namespace miniJson {

JsonType JsonValue::getType() const {
	if (std::holds_alternative<nullptr_t>(_val))
		return JsonType::Null;
	else if (std::holds_alternative<bool>(_val))
		return JsonType::Bool;
	else if (std::holds_alternative<double>(_val))
		return JsonType::Number;
	else 
		return JsonType::String;
}

nullptr_t JsonValue::toNull() const {
	try {
		return std::get<nullptr_t>(_val);
	}
	catch (const std::bad_variant_access&) {
		throw JsonException("not a null");
	}
}

bool JsonValue::toBool() const {
	try {
		return std::get<bool>(_val);
	}
	catch (const std::bad_variant_access&) {
		throw JsonException("not a bool");
	}
}

double JsonValue::toDouble() const {
	try {
		return std::get<double>(_val);
	}
	catch (const std::bad_variant_access&) {
		throw JsonException("not a double");
	}
}

std::string JsonValue::toString() const{
	try {
		return std::get<std::string>(_val);
	}
	catch (const std::bad_variant_access&) {
		throw JsonException("not a string");
	}
}

}// namespace miniJson