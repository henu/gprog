#ifndef NODES_CONDITIONALCONSTANT_HPP
#define NODES_CONDITIONALCONSTANT_HPP

#include "node.hpp"
#include "../value.hpp"
#include "../utils.hpp"

namespace Nodes
{

class ConditionalConstant : public Node
{

public:

	ConditionalConstant(Value const& value) : value(value) {}

	virtual unsigned getInputsSize() const { return 1; }
	virtual unsigned getOutputsSize() const { return 1; }

private:

	Value value;

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		if (isTrue(inputs[0])) {
			outputs[0].push_back(value);
		}
	}
};

}

#endif
