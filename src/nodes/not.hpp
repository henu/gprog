#ifndef NODES_NOT_HPP
#define NODES_NOT_HPP

#include "node.hpp"
#include "../utils.hpp"

namespace Nodes {

class Not : public Node
{

public:

	virtual unsigned getInputsSize() const { return 1; }
	virtual unsigned getOutputsSize() const { return 1; }

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		outputs[0].push_back(!isTrue(inputs[0]));
	}
};

}

#endif
