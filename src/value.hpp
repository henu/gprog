#ifndef VALUE_HPP
#define VALUE_HPP

#include <map>
#include <string>
#include <vector>

class Value
{

public:

	inline Value(long i) :
	type(INTEGER)
	{
		data.i = i;
	}

	inline Value(std::string const& str) :
	type(STRING)
	{
		data.str = new std::string(str);
	}

	inline Value(Value const& val)
	{
		copyFrom(val);
	}

	inline ~Value()
	{
		clean();
	}

	inline Value& operator=(Value const& val)
	{
		clean();
		copyFrom(val);
		return *this;
	}


	inline std::string toString() const
	{
		switch (type) {

		case INTEGER:
			return std::to_string(data.i);

		case FLOAT:
			return std::to_string(data.f);

		case VECTOR:
			{
				std::string result;
				for (unsigned i = 0; i < data.vec->size(); ++ i) {
					result += (*data.vec)[i].toString();
				}
				return result;
			}

		case STRING:
			return *data.str;

		default:
			return "";

		}
	}

private:

	typedef std::vector<Value> ValueVec;
	typedef std::map<std::string, Value> ValueMap;

	enum Type {
		TRUE,
		FALSE,
		NIL,
		INTEGER,
		FLOAT,
		VECTOR,
		MAP,
		STRING
	};

	union {
		long i;
		double f;
		ValueVec* vec;
		ValueMap* map;
		std::string* str;
	} data;

	Type type;

	inline void clean()
	{
		switch (type) {

		case VECTOR:
			delete data.vec;
			break;

		case MAP:
			delete data.map;
			break;

		case STRING:
			delete data.str;
			break;

		default:
			break;

		}
	}

	inline void copyFrom(Value const& val)
	{
		type = val.type;

		switch (type) {

		case INTEGER:
			data.i = val.data.i;
			break;

		case FLOAT:
			data.f = val.data.f;
			break;

		case VECTOR:
			data.vec = new ValueVec(*val.data.vec);
			break;

		case MAP:
			data.map = new ValueMap(*val.data.map);
			break;

		case STRING:
			data.str = new std::string(*val.data.str);
			break;

		default:
			break;

		}
	}
};

typedef std::vector<Value> Values;
typedef std::vector<Values> ValuesVec;

#endif