#ifndef JSON_HPP
#define JSON_HPP

#include <cmath>
#include <cstdlib>
#include <istream>
#include <map>
#include <streambuf>
#include <stdexcept>
#include <string>
#include <vector>

class JSON
{

public:

	enum Type {
		NOT_INITIALIZED,
		OBJECT,
		ARRAY,
		STRING,
		INTEGER,
		FLOAT,
		TRUE,
		FALSE,
		NIL
	};

	inline JSON() :
	type(NOT_INITIALIZED)
	{
	}

	inline JSON(std::string const& str)
	{
		std::string::const_iterator it = str.begin();
		read(it, str.end());
	}

	inline JSON(std::istream& strm)
	{
		std::string str((std::istreambuf_iterator<char>(strm)), std::istreambuf_iterator<char>());
		std::string::const_iterator it = str.begin();
		read(it, str.end());
	}

	inline bool contains(std::string const& key) const
	{
		if (type != OBJECT) {
			throw std::runtime_error("Not an object!");
		}
		return children.find(key) != children.end();
	}

	inline unsigned size() const
	{
		if (type == OBJECT) {
			return children.size();
		}
		if (type == ARRAY) {
			return items.size();
		}
		throw std::runtime_error("Not an object nor array!");
	}

	inline JSON get(std::string const& key) const
	{
		if (type != OBJECT) {
			throw std::runtime_error("Not an object!");
		}
		Children::const_iterator children_find = children.find(key);
		if (children_find == children.end()) {
			throw std::runtime_error("Key not found!");
		}
		return children_find->second;
	}

	inline JSON get(unsigned i) const
	{
		if (type != ARRAY) {
			throw std::runtime_error("Not an array!");
		}
		if (i >= items.size()) {
			throw std::runtime_error("Index overflow!");
		}
		return items[i];
	}

	inline std::string getString() const
	{
		if (type != STRING) {
			throw std::runtime_error("Not a string!");
		}
		return str;
	}

	inline long getInteger() const
	{
		if (type != INTEGER) {
			throw std::runtime_error("Not an integer!");
		}
		return num_i;
	}

	inline bool getBoolean() const
	{
		if (type == TRUE) {
			return true;
		} else if (type == FALSE) {
			return false;
		} else {
			throw std::runtime_error("Not a boolean!");
		}
	}

	inline bool isNull() const { return type == NIL; }
	inline bool isString() const { return type == STRING; }
	inline bool isInteger() const { return type == INTEGER; }

	inline std::string firstKey() const
	{
		if (type != OBJECT) {
			throw std::runtime_error("Not a string!");
		}
		if (children.empty()) {
			return "";
		}
		return children.begin()->first;
	}

	inline std::string nextKey(std::string const& key) const
	{
		if (type != OBJECT) {
			throw std::runtime_error("Not a string!");
		}
		Children::const_iterator children_find = children.upper_bound(key);
		if (children_find == children.end()) {
			return children.rbegin()->first + "-";
		}
		return children_find->first;
	}

private:

	typedef std::map<std::string, JSON> Children;
	typedef std::vector<JSON> Items;

	Type type;

	// Data for different types
	Children children;
	Items items;
	std::string str;
	float num;
	long num_i;

	inline void read(std::string::const_iterator& it, std::string::const_iterator const& end)
	{
		skipWhitespace(it, end);

		ensureNoEnd(it, end);

		// Object
		if (*it == '{') {
			++ it;

			type = OBJECT;

			skipWhitespace(it, end);
			ensureNoEnd(it, end);

			// If empty object
			if (*it == '}') {
				++ it;
			} else {
				while (true) {
					// Read key
					std::string key = readString(it, end);
					skipWhitespace(it, end);

					// Read colon
					ensureNoEnd(it, end);
					if (*it != ':') {
						throw std::runtime_error("Missing colon!");
					}
					++ it;

					JSON child;
					child.read(it, end);

					children[key] = child;

					skipWhitespace(it, end);
					ensureNoEnd(it, end);

					// If end of object
					if (*it == '}') {
						++ it;
						break;
					}
					// If there is more children
					else if (*it == ',') {
						++ it;
					}
					// If invalid character
					else {
						throw std::runtime_error("Unexpected character!");
					}

					skipWhitespace(it, end);
				}
			}
		}
		// Array
		else if (*it == '[') {
			++ it;

			type = ARRAY;

			skipWhitespace(it, end);
			ensureNoEnd(it, end);

			// If empty array
			if (*it == ']') {
				++ it;
			} else {
				while (true) {
					JSON item;
					item.read(it, end);

					items.push_back(item);

					skipWhitespace(it, end);
					ensureNoEnd(it, end);

					// If end of array
					if (*it == ']') {
						++ it;
						break;
					}
					// If there is more items
					else if (*it == ',') {
						++ it;
					}
					// If invalid character
					else {
						throw std::runtime_error("Unexpected character!");
					}

					skipWhitespace(it, end);
				}
			}
		}
		// String
		else if (*it == '"') {
			type = STRING;
			str = readString(it, end);
		}
		// Number
		else if ((*it >= '0' && *it <= '9') || *it == '-') {
			// Read to string first
			std::string number_s;
			bool dot_found = false;
			while (true) {
				number_s += *it;
				++ it;

				// If ends
				if (it == end) {
					break;
				}
				// Dot
				else if (*it == '.') {
					if (dot_found) {
						throw std::runtime_error("Unexpected second dot in number!");
					} else {
						dot_found = true;
					}
				}
				// If something else than number
				else if (*it < '0' || *it > '9') {
					break;
				}
			}
			if (number_s == "-") {
				throw std::runtime_error("Unexpected lonely minus sign!");
			}

			// Convert to number
			if (!dot_found) {
				type = INTEGER;
				num_i = strtol(number_s.c_str(), NULL, 10);
			} else {
				type = FLOAT;
				num = strtof(number_s.c_str(), NULL);
			}

		}
		// True
		else if (end - it >= 4 && std::string(it, it + 4) == "true") {
			type = TRUE;
			it += 4;
// TODO: Ensure this is followed by good character!
		}
		// False
		else if (end - it >= 5 && std::string(it, it + 5) == "false") {
			type = FALSE;
			it += 5;
// TODO: Ensure this is followed by good character!
		}
		// Null
		else if (end - it >= 4 && std::string(it, it + 4) == "null") {
			type = NIL;
			it += 4;
// TODO: Ensure this is followed by good character!
		}
		// Invalid type
		else {
			throw std::runtime_error("Unexpected character!");
		}
	}

	inline void skipWhitespace(std::string::const_iterator& it, std::string::const_iterator const& end)
	{
		while (it != end && (*it == ' ' || *it == '\n' || *it == '\t')) {
			++ it;
		}
	}

	inline void ensureNoEnd(std::string::const_iterator const& it, std::string::const_iterator const& end)
	{
		if (it == end) {
			throw std::runtime_error("Unexpected end!");
		}
	}

	inline std::string readString(std::string::const_iterator& it, std::string::const_iterator const& end)
	{
		skipWhitespace(it, end);
		ensureNoEnd(it, end);

		if (*it != '"') {
			throw std::runtime_error("Unexpected character!");
		}
		++ it;

		std::string str;
		while (true) {
			ensureNoEnd(it, end);
			// If string ends
			if (*it == '"') {
				++ it;
				break;
			}
			// If special character
			else if (*it == '\\') {
				++ it;
				ensureNoEnd(it, end);
				char c = *it;
				++ it;
				if (c == '\\') str += c;
				else if (c == '"') str += '"';
				else if (c == 'b') str += '\b';
				else if (c == 'f') str += '\f';
				else if (c == 'n') str += '\n';
				else if (c == 'r') str += '\r';
				else if (c == 't') str += '\t';
				else {
					throw std::runtime_error("Unexpected escaped character!");
				}
			}
			// Normal character
			else {
				str += *it;
				++ it;
			}
		}

		return str;
	}
};

#endif

