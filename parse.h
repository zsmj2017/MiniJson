#pragma once

#include "json.h"
#include "jsonException.h"

namespace json {

class Parser{
public:
	//为了便于解析，将string转为了const char*指针，以便于与叶大的json库对照
	Parser(const std::string& content) noexcept : _start(content.c_str()), _curr(content.c_str()) {}
	Json parse();
private:

	Json parseValue();
	Json parseLiteral(const std::string& literal);
	Json parseNumber();
	void parseWhitespace() noexcept;

	void error(const std::string& msg) const{ 
		throw JsonException(msg + ": " + _start); 
	}

	const char* _start;
	const char* _curr;
};
}