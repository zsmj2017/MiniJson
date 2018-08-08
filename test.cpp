#include <gtest\gtest.h>
#include <string>
#include "json.h"

using namespace json;
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
	testNumber(0.0, "-0.0");
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
