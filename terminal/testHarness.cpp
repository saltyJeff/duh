#include "testHarness.h"
#include "DuhSwitch.h"
#include "../src/DuhRead.h"
bool nibbleTest[] = {1, 0, 0, 1};
bool byteTest[] = {1, 1, 0, 1, 0, 0, 0, 1};
bool oddTest[] = {1, 1, 1};
bool longTest[] = {1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1};
void preTestEncode() {

}
void testEncode() {

}

void preTestRead() {
	char goodChecksum[] = "SW-the:0020/7C17;";
	char badChecksum[] = "SW-the:0020/69;";
	char noChecksum[] = "SW-the:0020;";

	int goodLen = strlen(goodChecksum);
	int badLen = strlen(badChecksum);
	int noLen = strlen(noChecksum);

	for(int i = 0; i < goodLen; i++) {
		char c = goodChecksum[i];
		byte readRes = readDuh(c);
		assert(readRes != SEND_NAK);
		if(c == ';') {
			assert(cachedInput.hasChecksum);
		}
	}
	for(int i = 0; i < badLen; i++) {
		char c = badChecksum[i];
		byte readRes = readDuh(c);
		assert(readRes != SEND_ACK);
		if(c == ';') {
			assert(cachedInput.hasChecksum);
		}
	}
	for(int i = 0; i < noLen; i++) {
		char c = noChecksum[i];
		byte readRes = readDuh(c);
		assert(readRes != SEND_NAK);
		if(c == ';') {
			assert(!cachedInput.hasChecksum);
		}
	}
}
void testRead() {
	assert(!strcmp(cachedInput.prefix, "SW"));
	assert(!strcmp(cachedInput.id, "the"));
	assert(!strcmp(cachedInput.data, "0020"));
}