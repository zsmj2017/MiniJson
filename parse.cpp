#include "parse.h"
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

namespace json {

constexpr bool is1to9(char ch) { return ch >= '1' && ch <= '9'; }
constexpr bool is0to9(char ch) { return ch >= '0' && ch <= '9'; }


void Parser::parseWhitespace() noexcept {
	while (*_curr == ' ' || *_curr == '\t' || *_curr == '\r' || *_curr == '\n')
		++_curr;
	_start = _curr;
}

Json Parser::parse() {
	parseWhitespace();
	Json json = parseValue();
	parseWhitespace();
	if (*_curr) //若消去空格后结尾仍存在字符
		error("ROOT NOT SINGULAR");
	return json;
}

Json Parser::parseValue() {
	switch (*_curr) {
	case 'n': return parseLiteral("null");
	case 't': return parseLiteral("true");
	case 'f': return parseLiteral("false");
	case '\0': error("EXPECT VALUE");
	default: return parseNumber();
	}
}

Json Parser::parseLiteral(const std::string & literal){
	if (strncmp(_curr, literal.c_str(), literal.size())) 
		error("INVALID VALUE");
	_curr += literal.size();
	_start = _curr;
	switch (literal[0]) {
	case 't': return Json(true);
	case 'f': return Json(false);
	default: return Json(nullptr);
	}
}

Json Parser::parseNumber(){
	if (*_curr== '-') ++_curr;
	if (*_curr== '0')
		++_curr;
	else {
		if (!is1to9(*_curr)) 
			error("INVALID VALUE");
		while (is0to9(*++_curr));
	}
	if (*_curr== '.') {
		if (!is0to9(*++_curr)) 
			error("INVALID VALUE");
		while (is0to9(*++_curr));
	}
	if (toupper(*_curr) == 'E') {
		++_curr;
		if (*_curr== '-' || *_curr== '+') 
			++_curr;
		if (!is0to9(*_curr)) 
			error("INVALID VALUE");
		while (is0to9(*++_curr));
	}
	double val = strtod(_start,nullptr);
	if (fabs(val) == HUGE_VAL) 
		error("NUMBER TOO BIG");
	_start = _curr;
	return Json(val);
}
}