#ifndef NODES_OR_HPP
#define NODES_OR_HPP

#include "node.hpp"
#include "../utils.hpp"

namespace Nodes {

class Or : public Node
{

public:

	virtual Node* clone() const { return new Or(); }

	virtual unsigned getInputsSize() const { return 2; }
	virtual unsigned getOutputsSize() const { return 1; }

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		outputs[0].push_back(isTrue(inputs[0]) || isTrue(inputs[1]));
	}
};

}

#endif
