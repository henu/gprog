#ifndef NODES_ISVALUE_HPP
#define NODES_ISVALUE_HPP

#include "node.hpp"
#include "../value.hpp"

namespace Nodes
{

class IsValue : public Node
{

public:

	IsValue(Value const& value) : value(value) {}

	virtual unsigned getInputsSize() const { return 1; }
	virtual unsigned getOutputsSize() const { return 1; }

private:

	Value value;

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;

		if (inputs[0].empty()) {
			return;
		}

		for (Value value : inputs[0]) {
			if (value != this->value) {
				outputs[0].push_back(Value(false));
				return;
			}
		}

		outputs[0].push_back(Value(true));
		return;
	}
};

}

#endif
