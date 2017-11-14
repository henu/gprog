#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include <map>

class Value
{

public:

	inline Value(long i) :
	type(INTEGER)
	{
		data.i = i;
	}

	inline Value(std::string const& str) :
	type(VECTOR)
	{
		data.vec = new ValueVec();
		data.vec->reserve(str.size());
		for (unsigned i = 0; i < str.size(); ++ i) {
			data.vec->push_back(Value(str[i]));
		}
	}

	inline ~Value()
	{
		switch (type) {

		case VECTOR:
			delete data.vec;
			break;

		case MAP:
			delete data.map;
			break;

		default:
			break;

		}
	}

private:

	typedef std::vector<Value> ValueVec;
	typedef std::map<ValueVec, Value> ValueMap;

	enum Type {
		TRUE,
		FALSE,
		NIL,
		INTEGER,
		FLOAT,
		VECTOR,
		MAP
	};

	union {
		long i;
		double f;
		ValueVec* vec;
		ValueMap* map;
	} data;

	Type type;
};

#endif
