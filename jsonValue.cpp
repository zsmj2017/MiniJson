#include "jsonValue.h"

namespace json {

JsonType json::JsonValue::getType() const{
	if (std::holds_alternative<nullptr_t>(_val))
		return JsonType::Null;
	else if (std::holds_alternative<bool>(_val))
		return JsonType::Bool;
	else if (std::holds_alternative<double>(_val))
		return JsonType::Number;
}

nullptr_t JsonValue::toNull() const{
	assert(std::holds_alternative<nullptr_t>(_val));
	return std::get<nullptr_t>(_val);
}

bool JsonValue::toBool() const{
	assert(std::holds_alternative<nullptr_t>(_val));
	return std::get<bool>(_val);
}

double JsonValue::toDouble() const{
	assert(std::holds_alternative<double>(_val));
	return std::get<double>(_val);
}
}
