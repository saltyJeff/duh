//
// Created by Jefferson on 9/29/2019.
//

#ifndef DUH_WRITETESTS_CPP
#define DUH_WRITETESTS_CPP

#include "../src/DuhInput.h"
#include "../catch/catch.h"
#include "../compat/compat.h"
#include "../src/DuhRead.h"
#include "testUtils.h"

TEST_CASE("serializes valid input") {
	TestInput valid("SW", "the", "0020");
	valid.serialize();
	REQUIRE(streq(writeBuffer, "SW-the:0020/7C17;"));
}
TEST_CASE("serializes shorter ids") {
	TestInput valid("W", "th", "0020");
	valid.serialize();
	REQUIRE(streq(writeBuffer, "W-th:0020/265E;"));
}
TEST_CASE("cuts over long fields") {
	TestInput valid("SWWWWWWW", "theEEEEEEEE", "0020");
	valid.serialize();
	REQUIRE(streq(writeBuffer, "SW-the:0020/7C17;"));
}
#endif //DUH_WRITETESTS_CPP
