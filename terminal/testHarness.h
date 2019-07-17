//
// Created by Jefferson on 6/15/2019.
//

#ifndef DUH_TESTHARNESS_H
#define DUH_TESTHARNESS_H

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

void preTestEncode();
void testEncode();

void preTestRead();
void testRead();

inline void test() {
	cout << "BEGINNING UNIT TESTS (to disable, take out the DEBUG define)" << endl;
	preTestEncode();
	testEncode();
	cout << "Encode tests passed" << endl;

	preTestRead();
	testRead();
	cout << "Read tests passed" << endl;
	cout << "All tests passed" << endl;
}


#endif //DUH_TESTHARNESS_H
