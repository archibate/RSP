#pragma once

#include <sstream>

#define SSTHROW(...) do { \
	std::ostringstream __os; \
	__os << __VA_ARGS__; \
	throw __os.str(); \
} while (0);
