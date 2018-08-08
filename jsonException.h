#pragma once

#include <stdexcept>

namespace json{
class JsonException: public std::runtime_error {
public:

	explicit JsonException(const std::string& errMsg) : runtime_error(errMsg) {}
	const char* what() const noexcept override {
		return runtime_error::what();
	}
};
}
