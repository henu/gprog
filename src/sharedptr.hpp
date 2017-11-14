#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include <cassert>

template<class T> class SharedPtr
{

public:

	inline SharedPtr() :
	obj(NULL)
	{
	}

	inline SharedPtr(T* obj) :
	obj(obj)
	{
		if (obj) {
			obj->increaseReferenceCount();
		}
	}

	inline SharedPtr(SharedPtr<T> const& other) :
	obj(other.obj)
	{
		if (obj) {
			obj->increaseReferenceCount();
		}
	}

	inline ~SharedPtr()
	{
		if (obj) {
			obj->decreaseReferenceCount();
			if (obj->getReferenceCount() == 0) {
				delete obj;
			}
		}
	}

	inline SharedPtr<T>& operator=(T* other_obj)
	{
		if (obj) {
			obj->decreaseReferenceCount();
			if (obj->getReferenceCount() == 0) {
				delete obj;
			}
		}
		obj = other_obj;
		if (obj) {
			obj->increaseReferenceCount();
		}
		return *this;
	}

	inline SharedPtr<T>& operator=(SharedPtr<T> const& other)
	{
		if (obj) {
			obj->decreaseReferenceCount();
			if (obj->getReferenceCount() == 0) {
				delete obj;
			}
		}
		obj = other.obj;
		if (obj) {
			obj->increaseReferenceCount();
		}
		return *this;
	}

	inline T* operator->()
	{
		assert(obj);
		return obj;
	}

	inline bool isNull() const
	{
		return !obj;
	}

	inline bool notNull() const
	{
		return obj;
	}

	inline T* get() const
	{
		return obj;
	}

private:

	T* obj;
};

#endif
