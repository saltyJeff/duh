#include "testHarness.h"
#include "../src/DuhSwitch.h"
bool nibbleTest[] = {1, 0, 0, 1};
bool byteTest[] = {1, 1, 0, 1, 0, 0, 0, 1};
bool oddTest[] = {1, 1, 1};
bool longTest[] = {1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1};
void preTestEncode() {

}
void testEncode() {
	encodeBuffer(nibbleTest, 4);
	assert(!strcmp(strEncodeBuffer, "9"));
	encodeBuffer(byteTest, 8);
	assert(!strcmp(strEncodeBuffer, "D1"));
	encodeBuffer(oddTest, 3);
	assert(!strcmp(strEncodeBuffer, "E"));
	encodeBuffer(longTest, 11);
	assert(!strcmp(strEncodeBuffer, "D12"));
}