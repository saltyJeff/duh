//
// Created by Jefferson on 9/30/2019.
//

#ifndef DUH_TESTUTILS_H
#define DUH_TESTUTILS_H

#include "../src/DuhInput.h"

class TestInput: public DuhInput {
public:
	char *data;
	TestInput(char *prefix, char *id, char *data): DuhInput(prefix, id) {
		this->data = data;
	}
	virtual char *encodeData () {
		return data;
	}
	virtual bool dirty () {
		return true;
	}
};

inline bool streq(const char *s1, const char *s2) {
	return !strcmp(s1, s2);
}
inline bool duhEqual(DuhInputCache a, TestInput b) {
	return streq(a.prefix, b.prefix) &&
		streq(a.id, b.id) &&
		streq(a.data, b.data);
}
inline bool duhEqual(TestInput a, DuhInputCache b) {
	return duhEqual(b, a);
}

#endif //DUH_TESTUTILS_H
