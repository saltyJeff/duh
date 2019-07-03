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

inline void test() {
	preTestEncode();
	testEncode();
	cout << "Encode tests passed" << endl;

	cout << "All tests passed" << endl;
}


#endif //DUH_TESTHARNESS_H
