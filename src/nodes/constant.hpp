#ifndef NODES_CONSTANT_HPP
#define NODES_CONSTANT_HPP

#include "node.hpp"
#include "../value.hpp"

namespace Nodes
{

class Constant : public Node
{

public:

	inline Constant(std::string const& str) : val(str) { }

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

	virtual void doRunning(ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)inputs;
		outputs[0].push_back(val);
	}
};

}

#endif