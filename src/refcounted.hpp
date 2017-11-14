#ifndef REFCOUNTED_HPP
#define REFCOUNTED_HPP

#include <cassert>

class RefCounted
{
public:

	RefCounted() :
	reference_count(0)
	{
	}

	unsigned reference_count;

	unsigned getReferenceCount() const
	{
		return reference_count;
	}

	void increaseReferenceCount()
	{
		++ reference_count;
	}

	void decreaseReferenceCount()
	{
		assert(reference_count > 0);
		-- reference_count;
	}

private:

};

#endif
