#ifndef BZUTIL_H
#define BZUTIL_H

#include "assert.h"
#include <cstdio>

#define bzzert(x, s) \
	do { if (!(x)) { printf("%s\n", s); assert((x)); } } while (0)

#endif
