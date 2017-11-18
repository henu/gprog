#ifndef VALUE_HPP
#define VALUE_HPP

#include "json.hpp"

#include <map>
#include <string>
#include <vector>

class Value
{

public:

	inline Value(bool b)
	{
		if (b) {
			type = TRUE;
		} else {
			type = FALSE;
		}
	}

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

	inline Value(JSON const& json)
	{
		if (json.isString()) {
			type = STRING;
			data.str = new std::string(json.getString());
		} else {
			throw std::runtime_error("That JSON to Value conversion is not supported yet!");
		}
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

	inline bool operator==(Value const& val) const
	{
		// Special case. Numbers can be same,
		// even if they have different types.
		if (type == INTEGER) {
			if (val.type == INTEGER) {
				return data.i == val.data.i;
			} else if (val.type == FLOAT) {
				return data.i == val.data.f;
			}
		} else if (type == FLOAT) {
			if (val.type == INTEGER) {
				return data.f == val.data.i;
			} else if (val.type == FLOAT) {
				return data.f == val.data.f;
			}
		}

		if (type != val.type) {
			return false;
		}

		switch (type) {
		case TRUE:
		case FALSE:
		case NIL:
			return true;
		case INTEGER:
		case FLOAT:
			// This should not be reached
			return false;
		case VECTOR:
			return *data.vec == *val.data.vec;
		case MAP:
			return *data.map == *val.data.map;
		case STRING:
			return *data.str == *val.data.str;
		}			return *data.vec == *val.data.vec;

	}

	inline bool operator!=(Value const& val) const
	{
		return !(*this == val);
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

	inline bool toBool() const
	{
		switch (type) {
		case TRUE:
			return true;
		case FALSE:
			return false;
		case NIL:
			return true;
		case INTEGER:
			return data.i != 0;
		case FLOAT:
			return data.f != 0;
		case VECTOR:
			return !data.vec->empty();
		case MAP:
			return !data.map->empty();
		case STRING:
			return !data.str->empty();
		}
		return false;
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
