#pragma once

#include "json.h"
#include "jsonException.h"

namespace miniJson {

class Parser{
public:// ctor
	explicit Parser(const char* cstr) noexcept:_start(cstr),_curr(cstr) {}
	explicit Parser(const std::string& content) noexcept : _start(content.c_str()), _curr(content.c_str()) {}

public:// uncopyable
	Parser(Parser&) = delete;
	Parser& operator=(Parser&) = delete;

public:// only public parse
	Json parse();

private:// parse interface
	Json parseValue();
	Json parseLiteral(const std::string& literal);
	Json parseNumber();
	Json parseString();

private:// parse_aux interface
	void parseWhitespace() noexcept;
	unsigned parse4hex();
	std::string encodeUTF8(unsigned u) noexcept;
	void error(const std::string& msg) const;

private:// private data member
	// two const char* points to the valid context's cur pos and start pos
	const char* _start;
	const char* _curr;
};
}