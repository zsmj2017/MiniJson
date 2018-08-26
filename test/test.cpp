#include <gtest\gtest.h>
#include <string>
#include "json.h"

using namespace miniJson;
using namespace std;

Json parseOk(const string& strJson) {
	string errMsg;
	Json json = Json::parse(strJson, errMsg);
	EXPECT_EQ(errMsg, "");
	return json;
}

#define testError(expect, strJson)            \
  do {                                        \
    string errMsg;                            \
    Json json = Json::parse(strJson, errMsg); \
    auto pos = errMsg.find_first_of(":");     \
    auto actual = errMsg.substr(0, pos);      \
    EXPECT_EQ(actual, expect);                \
  } while (0)


#define testNull(strJson)         \
  do {                            \
    Json json = parseOk(strJson); \
    EXPECT_TRUE(json.isNull());   \
  } while (0)

#define testBool(expect, content)      \
  do {                                 \
    Json json = parseOk(content);      \
    EXPECT_TRUE(json.isBool());        \
    EXPECT_EQ(json.toBool(), expect);  \
    json = Json(!expect);              \
    EXPECT_EQ(json.toBool(), !expect); \
  } while (0)

#define testNumber(expect, strJson)     \
  do {                                  \
    Json json = parseOk(strJson);       \
    EXPECT_TRUE(json.isNumber());       \
    EXPECT_EQ(json.toDouble(), expect); \
  } while (0)

#define testString(expect, strJson)     \
  do {                                  \
    Json json = parseOk(strJson);       \
    EXPECT_TRUE(json.isString());       \
    EXPECT_EQ(json.toString(), expect); \
  } while (0)

#define testRoundtrip(expect)                                              \
  do {                                                                     \
    Json json = parseOk(expect);                                           \
    string actual = json.serialize();                                      \
    if (json.isNumber())                                                   \
      EXPECT_EQ(strtod(actual.c_str(), nullptr), strtod(expect, nullptr)); \
    else                                                                   \
      EXPECT_EQ(actual, expect);                                           \
  } while (0)

TEST(Str2Json, JsonNull) {
	testNull("null");
	testNull("   null\n\r\t");
}

TEST(Str2Json, JsonBool) {
	testBool(true, "true");
	testBool(false, "false");
}

TEST(Str2Json, JsonNumber) {
	testNumber(0.0, "0");
	testNumber(0.0, "-0");
	testNumber(0.0, "0.0");
	testNumber(1.0, "1");
	testNumber(-1.0, "-1");
	testNumber(1.5, "1.5");
	testNumber(-1.5, "-1.5");
	testNumber(3.1416, "3.1416");
	testNumber(1E10, "1E10");
	testNumber(1e10, "1e10");
	testNumber(1E+10, "1E+10");
	testNumber(1E-10, "1E-10");
	testNumber(-1E10, "-1E10");
	testNumber(-1e10, "-1e10");
	testNumber(-1E+10, "-1E+10");
	testNumber(-1E-10, "-1E-10");
	testNumber(1.234E+10, "1.234E+10");
	testNumber(1.234E-10, "1.234E-10");
	testNumber(5.0E-324, "5e-324");
	testNumber(0, "1e-10000");
	testNumber(1.0000000000000002, "1.0000000000000002");
	testNumber(4.9406564584124654e-324, "4.9406564584124654e-324");
	testNumber(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	testNumber(2.2250738585072009e-308, "2.2250738585072009e-308");
	testNumber(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	testNumber(2.2250738585072014e-308, "2.2250738585072014e-308");
	testNumber(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	testNumber(1.7976931348623157e+308, "1.7976931348623157e+308");
	testNumber(-1.7976931348623157e+308, "-1.7976931348623157e+308");
	string errMsg;
	Json json = Json::parse("1.2e+12", errMsg);
	EXPECT_TRUE(json.isNumber());
	json = Json(3.1415);
	EXPECT_EQ(3.1415, json.toDouble());
}

TEST(Str2Json, JsonString) {
  testString("", "\"\"");
  testString("Hello", "\"Hello\"");
  testString("Hello\nWorld", "\"Hello\\nWorld\"");
  testString("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
  string s = "Hello";
  s.push_back('\0');
  s += "World";
  testString(s, "\"Hello\\u0000World\"");
  testString("\x24", "\"\\u0024\"");
  testString("\xC2\xA2", "\"\\u00A2\"");
  testString("\xE2\x82\xAC", "\"\\u20AC\"");
  testString("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");
  testString("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"");
  string errMsg;
  Json json = Json::parse("\"something\"", errMsg);
  json = Json("another thing");
  EXPECT_EQ(json.toString(), "another thing");
}

TEST(Str2Json, JsonArray) {
	Json json = parseOk("[ ]");
	EXPECT_TRUE(json.isArray());
	EXPECT_EQ(json.size(), 0);

	json = parseOk("[ null , false , true , 123 , \"abc\" ]");
	EXPECT_TRUE(json.isArray());
	EXPECT_EQ(json.size(), 5);
	EXPECT_EQ(json[0], Json(nullptr));
	EXPECT_EQ(json[1], Json(false));
	EXPECT_EQ(json[2], Json(true));
	EXPECT_EQ(json[3], Json(123.0));
	EXPECT_EQ(json[4], Json("abc"));

	json = parseOk("[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]");
	EXPECT_TRUE(json.isArray());
	EXPECT_EQ(json.size(), 4);

	EXPECT_TRUE(json[0].isArray());
	EXPECT_EQ(json[0].size(), 0);

	EXPECT_TRUE(json[1].isArray());
	EXPECT_EQ(json[1].size(), 1);
	EXPECT_EQ(json[1][0].toDouble(), 0);

	EXPECT_TRUE(json[2].isArray());
	EXPECT_EQ(json[2].size(), 2);
	EXPECT_EQ(json[2][0].toDouble(), 0);
	EXPECT_EQ(json[2][1].toDouble(), 1);

	EXPECT_TRUE(json[3].isArray());
	EXPECT_EQ(json[3].size(), 3);
	EXPECT_EQ(json[3][0].toDouble(), 0);
	EXPECT_EQ(json[3][1].toDouble(), 1);
	EXPECT_EQ(json[3][2].toDouble(), 2);
}

TEST(Str2Json, JsonObject) {
	Json json = parseOk("{ }");
	EXPECT_TRUE(json.isObject());
	EXPECT_EQ(json.size(), 0);

	json = parseOk(" { "
		"\"n\" : null , "
		"\"f\" : false , "
		"\"t\" : true , "
		"\"i\" : 123 , "
		"\"s\" : \"abc\", "
		"\"a\" : [ 1, 2, 3 ],"
		"\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
		" } ");
	EXPECT_TRUE(json.isObject());
	EXPECT_EQ(json.size(), 7);

	EXPECT_TRUE(json["n"].isNull());

	EXPECT_TRUE(json["f"].isBool());
	EXPECT_EQ(json["f"].toBool(), false);

	EXPECT_TRUE(json["t"].isBool());
	EXPECT_EQ(json["t"].toBool(), true);

	EXPECT_TRUE(json["i"].isNumber());
	EXPECT_EQ(json["i"].toDouble(), 123.0);

	EXPECT_TRUE(json["s"].isString());
	EXPECT_EQ(json["s"].toString(), "abc");

	EXPECT_TRUE(json["a"].isArray());
	EXPECT_EQ(json["a"].size(), 3);

	EXPECT_TRUE(json["o"].isObject());
	EXPECT_EQ(json["o"].size(), 3);
}

TEST(RoundTrip, literal) {
	testRoundtrip("null");
	testRoundtrip("true");
	testRoundtrip("false");
}

TEST(RoundTrip, JsonNumber) {
	testRoundtrip("0");
	testRoundtrip("-0");
	testRoundtrip("1");
	testRoundtrip("-0");
	testRoundtrip("1.5");
	testRoundtrip("-1.5");
	testRoundtrip("3.25");
	testRoundtrip("1e+20");
	testRoundtrip("1.234e+20");
	testRoundtrip("1.234e-20");
	testRoundtrip("1.0000000000000002");
	testRoundtrip("4.9406564584124654e-324");
	testRoundtrip("-4.9406564584124654e-324");
	testRoundtrip("2.2250738585072009e-308");
	testRoundtrip("-2.2250738585072009e-308");
	testRoundtrip("2.2250738585072014e-308");
	testRoundtrip("-2.2250738585072014e-308");
	testRoundtrip("1.7976931348623157e+308");
	testRoundtrip("-1.7976931348623157e+308");
}

TEST(RoundTrip, JsonString) {
	testRoundtrip("\"\"");
	testRoundtrip("\"Hello\"");
	testRoundtrip("\"Hello\\nWorld\"");
	testRoundtrip("\"\\\" \\\\ / \\b \\f \\n \\r \\t\"");
	testRoundtrip("\"Hello\\u0000World\"");
}

TEST(RoundTrip, JsonArray) {
	testRoundtrip("[  ]");
	testRoundtrip("[ null, false, true, 123, \"abc\", [ 1, 2, 3 ] ]");
}

TEST(RoundTrip, JsonObject) {
	testRoundtrip("{  }");
	testRoundtrip(R"({ "n": null, "f": false, "t": true, "i": 123, "a": [ 1, 2, 3 ], "s": "abc", "o": { "1": 1, "2": 2, "3": 3 } })");
}

TEST(Error, ExpectValue) {
	testError("EXPECT VALUE", "");
	testError("EXPECT VALUE", " ");
}

TEST(Error, InvalidValue) {
	testError("INVALID VALUE", "nul");
	testError("INVALID VALUE", "?");
	testError("INVALID VALUE", "+0");
	testError("INVALID VALUE", "+1");
	testError("INVALID VALUE", ".123");
	testError("INVALID VALUE", "1.");
	testError("INVALID VALUE", "inf");
	testError("INVALID VALUE", "INF");
	testError("INVALID VALUE", "NAN");
	testError("INVALID VALUE", "nan");
	testError("INVALID VALUE", "[1,]");
	testError("INVALID VALUE", "[\"a\", nul]");
}

TEST(Error, RootNotSingular) {
	testError("ROOT NOT SINGULAR", "null x");
	testError("ROOT NOT SINGULAR", "0123");
	testError("ROOT NOT SINGULAR", "0x0");
	testError("ROOT NOT SINGULAR", "0x123");
}

TEST(Error, NumberTooBig) {
	testError("NUMBER TOO BIG", "1e309");
	testError("NUMBER TOO BIG", "-1e309");
}

TEST(Error, MissQuotationMark) {
	testError("MISS QUOTATION MARK", "\"");
	testError("MISS QUOTATION MARK", "\"abc");
}

TEST(Error, InvalidStringEscape) {
	testError("INVALID STRING ESCAPE", "\"\\v\"");
	testError("INVALID STRING ESCAPE", "\"\\'\"");
	testError("INVALID STRING ESCAPE", "\"\\0\"");
	testError("INVALID STRING ESCAPE", "\"\\x12\"");
}

TEST(Error, InvalidStringChar) {
	testError("INVALID STRING CHAR", "\"\x01\"");
	testError("INVALID STRING CHAR", "\"\x1F\"");
}

TEST(Error, InvalidUnicodeHex) {
	testError("INVALID UNICODE HEX", "\"\\u\"");
	testError("INVALID UNICODE HEX", "\"\\u0\"");
	testError("INVALID UNICODE HEX", "\"\\u01\"");
	testError("INVALID UNICODE HEX", "\"\\u012\"");
	testError("INVALID UNICODE HEX", "\"\\u/000\"");
	testError("INVALID UNICODE HEX", "\"\\uG000\"");
	testError("INVALID UNICODE HEX", "\"\\u0/00\"");
	testError("INVALID UNICODE HEX", "\"\\u0G00\"");
	testError("INVALID UNICODE HEX", "\"\\u000/\"");
	testError("INVALID UNICODE HEX", "\"\\u00G/\"");
	testError("INVALID UNICODE HEX", "\"\\u 123/\"");
}

TEST(Error, InvalidUnicodeSurrogate) {
	testError("INVALID UNICODE SURROGATE", "\"\\uD800\"");
	testError("INVALID UNICODE SURROGATE", "\"\\uDBFF\"");
	testError("INVALID UNICODE SURROGATE", "\"\\uD800\\\\\\");
	testError("INVALID UNICODE SURROGATE", "\"\\uD800\\uDBFF\"");
	testError("INVALID UNICODE SURROGATE", "\"\\uD800\\uE000\"");
}

TEST(Error, MissCommaOrSquareBracket) {
	testError("MISS COMMA OR SQUARE BRACKET", "[1");
	testError("MISS COMMA OR SQUARE BRACKET", "[1}");
	testError("MISS COMMA OR SQUARE BRACKET", "[1 2");
	testError("MISS COMMA OR SQUARE BRACKET", "[[]");
}

TEST(Error, MissKey) {
	testError("MISS KEY", "{:1,");
	testError("MISS KEY", "{1:1,");
	testError("MISS KEY", "{true:1,");
	testError("MISS KEY", "{false:1,");
	testError("MISS KEY", "{null:1,");
	testError("MISS KEY", "{[]:1,");
	testError("MISS KEY", "{{}:1,");
	testError("MISS KEY", "{\"a\":1,");
}

TEST(Error, MissColon) {
	testError("MISS COLON", "{\"a\"}");
	testError("MISS COLON", "{\"a\",\"b\"}");
}

TEST(Error, MissCommaOrCurlyBracket) {
	testError("MISS COMMA OR CURLY BRACKET", "{\"a\":1");
	testError("MISS COMMA OR CURLY BRACKET", "{\"a\":1]");
	testError("MISS COMMA OR CURLY BRACKET", "{\"a\":1 \"b\"");
	testError("MISS COMMA OR CURLY BRACKET", "{\"a\":{}");
}

TEST(Json, Ctor) {
	{
		Json json;
		EXPECT_TRUE(json.isNull());
	}
	{
		Json json(nullptr);
		EXPECT_TRUE(json.isNull());
	}
	{
		Json json(true);
		EXPECT_TRUE(json.isBool());
		EXPECT_EQ(json.toBool(), true);

		Json json1(false);
		EXPECT_TRUE(json1.isBool());
		EXPECT_EQ(json1.toBool(), false);
	}
	{
		Json json(0);
		EXPECT_TRUE(json.isNumber());
		EXPECT_EQ(json.toDouble(), 0);

		Json json1(100.1);
		EXPECT_TRUE(json1.isNumber());
		EXPECT_EQ(json1.toDouble(), 100.1);
	}
	{
		Json json("hello");
		EXPECT_TRUE(json.isString());
		EXPECT_EQ(json.toString(), "hello");
	}
	{
		vector<Json> arr{ Json(nullptr), Json(true), Json(1.2) };
		Json json(arr);
		EXPECT_TRUE(json.isArray());
		EXPECT_TRUE(json[0].isNull());
	}
	{
		unordered_map<string, Json> obj;
		obj.insert({ "hello", Json(nullptr) });
		obj.insert({ "world", Json("!!") });
		Json json(obj);
		EXPECT_TRUE(json.isObject());
		EXPECT_TRUE(json["world"].isString());
	}
	{
		Json json = Json::_object{
			{ "key1", "value1" },
			{ "key2", false },
			{ "key3", Json::_array{ 1, 2, 3 } },
		};
		EXPECT_TRUE(json.isObject());
		EXPECT_TRUE(json["key1"].isString());
		EXPECT_EQ(json["key1"].toString(),"value1");
		EXPECT_TRUE(json["key2"].isBool());
		EXPECT_EQ(json["key2"].toBool(), false);
		EXPECT_TRUE(json["key3"].isArray());
		EXPECT_EQ(json["key3"][1].toDouble(), 2);
	}
}