//
// Created by Jefferson on 9/29/2019.
//

#ifndef DUH_READTESTS_PP
#define DUH_READTESTS_PP
#include "../catch/catch.h"
#include "../compat/compat.h"
#include "../src/DuhRead.h"
#include "../catch/streq.h"

char goodChecksum[] = "SW-the:0020/7C17;";
char badChecksum[] = "AB-cde:0020/69;";
char noChecksum[] = "aa-bb:0020;";
char multipleInvalids[] = "abcdef/ja;dkel234;d/asdf;2;lk34j;a021349-09-0932j3943-;SW-the:0020;";

int goodLen = strlen(goodChecksum);
int badLen = strlen(badChecksum);
int noLen = strlen(noChecksum);
int multiLen = strlen(multipleInvalids);

TEST_CASE("parses valid checksum") {
	SECTION("parsing") {
		for (int i = 0; i < goodLen; i++) {
			char c = goodChecksum[i];
			byte readRes = readDuh(c);
			REQUIRE(readRes != SEND_NAK);
			if (c == ';') {
				REQUIRE(readRes == SEND_ACK);
			}
		}
	}
	SECTION("result") {
		CHECK( streq(input.prefix, "SW") );
		CHECK( streq(input.id, "the") );
		CHECK( streq(input.data, "0020") );
		CHECK( streq(input.checksum, "7C17") );
	}
}
TEST_CASE("parses invalid checksum") {
	SECTION("parsing") {
		for (int i = 0; i < badLen; i++) {
			char c = badChecksum[i];
			byte readRes = readDuh(c);

			REQUIRE(readRes != SEND_ACK);
			if (c == ';') {
				REQUIRE(readRes == SEND_NAK);
			}
		}
	}
}
TEST_CASE("parses no checksum") {
	SECTION("parsing") {
		for (int i = 0; i < noLen; i++) {
			char c = noChecksum[i];
			byte readRes = readDuh(c);
			REQUIRE(readRes != SEND_NAK);
			if (c == ';') {
				REQUIRE(readRes == SEND_ACK);
			}
		}
	}
	SECTION("result") {
		CHECK( streq(input.prefix, "aa") );
		CHECK( streq(input.id, "bb") );
		CHECK( streq(input.data, "0020") );
	}
}
TEST_CASE("parses garbage") {
	SECTION("parsing") {
		for (int i = 0; i < multiLen; i++) {
			char c = multipleInvalids[i];
			byte readRes = readDuh(c);
			if(i != multiLen - 1) {
				REQUIRE( readRes != SEND_ACK );
			}
			else {
				REQUIRE(readRes == SEND_ACK);
			}
		}
	}
	SECTION("result") {
		CHECK( streq(input.prefix, "SW") );
		CHECK( streq(input.id, "the") );
		CHECK( streq(input.data, "0020") );
	}
}
#endif //DUH_READTESTS_PP