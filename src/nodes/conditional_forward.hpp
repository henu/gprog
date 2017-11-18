#ifndef NODES_CONDITIONALFORWARD_HPP
#define NODES_CONDITIONALFORWARD_HPP

#include "node.hpp"
#include "../utils.hpp"

namespace Nodes
{

class ConditionalForward : public Nodes::Node
{

public:

	virtual unsigned getInputsSize() const { return 2; }
	virtual unsigned getOutputsSize() const { return 1; }

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		if (isTrue(inputs[1])) {
			outputs[0] = inputs[0];
		}
	}
};

}

#endif
