#ifndef NODES_CAPTURER_HPP
#define NODES_CAPTURER_HPP

#include "node.hpp"

#include <cassert>

namespace Nodes
{

class Capturer : public Node
{

public:

	virtual Node* clone() const { return new Capturer(); }

	inline std::string getContent(State const* state) const
	{
		assert(state);
		std::string const* statedata = (std::string const*)state->getData();
		return *statedata;
	}

	virtual unsigned getInputsSize() const
	{
		return 1;
	}

	virtual void* initializeStateData() const
	{
		return new std::string();
	}

	virtual void cleanStateData(void* data) const
	{
		std::string* statedata = (std::string*)data;
		delete statedata;
	}

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		(void)outputs;
		std::string* statedata = (std::string*)state->getData();
		Values const& values = inputs[0];
		for (unsigned i = 0; i < values.size(); ++ i) {
			*statedata += values[i].toString();
		}
	}
};

}

#endif
