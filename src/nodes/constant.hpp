#ifndef NODES_CONSTANT_HPP
#define NODES_CONSTANT_HPP

#include "node.hpp"
#include "../value.hpp"

namespace Nodes
{

class Constant : public Node
{

public:

	inline Constant(Value const& val) : val(val) { }

	virtual unsigned getOutputsSize() const
	{
		return 1;
	}

	virtual bool isInitiallyActive() const
	{
		return true;
	}

private:

	Value val;

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		(void)inputs;
		outputs[0].push_back(val);
	}
};

}

#endif
