MiniJson
----------
[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)

JSON is a lightweight data-interchange format. It can represent numbers, strings, ordered sequences of values, and collections of name/value pairs.

MiniJson is a tiny JSON library that allows manipulating JSON values, including serialization and deserialization to and from strings. 

MiniJson is written in C++17 and test the code using the GoogleTest framework.The classes are heavily unit-tested and covers 100% of the code, including all exceptional behavior. 


----------
The core object provided by the library is MiniJson::Json. A Json object represents any JSON value: null(nullptr_t), bool, number (int or double), string(std::string), array(std::vector), or object (std::unordered_map).

Json objects act like values. They can be assigned, copied, moved, compared for equality and so on. There are also helper methods Json::serialize, to serialize a Json to a string, and Json::parse (static) to parse a std::string or const char* as a Json object.

----------
We can construct a JSON object very intuitively:
```C++
Json my_json1(nullptr);
Json my_json2 = "string";

Json my_json3 = Json::_object {
    { "key1", "value1" },
    { "key2", false },
    { "key3", Json::_array { 1, 2, 3 } },
};
```
String can be expressed explicitly using Json::parse() easily:
```C++
string errMsg;// store error messages when catch a exception in parse process
auto js = Json::parse("[ null , false , true , 123 , \"abc\" ]",errmsg);
cout << js[4] << endl;
```
You can also get a string representation of a JSON value (serialize):
```C++
auto str = js.serialize();
```
Even you can try to output the JSON object directly:
```C++
cout << js << endl;
```

----------
More documentation is still to come. For now, please see Json.h.

