#include <gtest\gtest.h>
#include "json.h"
#include <iostream>
#include <variant>

using namespace::std;
using namespace::miniJson;

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}