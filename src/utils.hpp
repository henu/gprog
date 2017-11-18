#ifndef UTILS_HPP
#define UTILS_HPP

#include "value.hpp"

inline bool isTrue(Values const& vals)
{
	for (Value const& val : vals) {
		if (val.toBool()) {
			return true;
		}
	}
	return false;
}

#endif
