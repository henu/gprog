#ifndef UTILS_HPP
#define UTILS_HPP

#include "value.hpp"

inline bool isTrue(Values const& vals)
{
	if (vals.empty()) return false;
	for (Value const& val : vals) {
		if (val.toBool()) {
			return true;
		}
	}
	return false;
}

#endif
