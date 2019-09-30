//
// Created by Jefferson on 9/30/2019.
//

#include "../catch/catch.h"
#include "../src/DuhRead.h"
#include "testUtils.h"

const byte expectedInputs = 3;

TEST_CASE("parse a stream of valid characters") {
	const byte expectedInputs = 3;
	std::string stream = ";";
	DuhInputCache parsedInputs[expectedInputs];

	TestInput inputs[expectedInputs] = {
			TestInput("ab", "cde", "1010"),
			TestInput("po", "tat", "000000"),
			TestInput("pp", "ap", "3154"),
	};

	for(int i = 0; i < 3; i++) {
		inputs[i].serialize();
		stream += std::string(writeBuffer);
	}
	int i = 0;
	for(char c : stream) {
		byte result = readDuh(c);
		if(result == SEND_ACK) {
			DuhInputCache copy = parsed;
			parsedInputs[i++] = copy;
		}
	}

	SECTION("check parsed inputs for validity") {
		for(int i = 0; i < 3; i++) {
			//printf("index %d\n", i);
			CHECK(duhEqual(inputs[i], parsedInputs[i]));
		}
	}
}

TEST_CASE("parse a stream with noise") {
	std::string stream = ";";
	DuhInputCache parsedInputs[expectedInputs];
	char noises[expectedInputs][32] = { // all noises should end with a semicolon as a delim
			"ababababa;",
			"a-3/3343;2-234./;",
			"?234aaj;lkj84"
	};

	TestInput inputs[expectedInputs] = {
			TestInput("ab", "cde", "1010"),
			TestInput("po", "tat", "000000"),
			TestInput("pp", "ap", "3154"),
	};

	for(int i = 0; i < 3; i++) {
		inputs[i].serialize();
		stream += std::string(writeBuffer);
		stream += noises[i];
	}
	int i = 0;
	for(char c : stream) {
		byte result = readDuh(c);
		if(result == SEND_ACK) {
			DuhInputCache copy = parsed;
			parsedInputs[i++] = copy;
		}
	}

	SECTION("check parsed inputs for validity") {
		for(int i = 0; i < 3; i++) {
			//printf("index %d id %s:\n", i, parsedInputs[i].id);
			CHECK(duhEqual(inputs[i], parsedInputs[i]));
		}
	}
}