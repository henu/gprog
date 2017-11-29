#ifndef NODES_STDOUT_HPP
#define NODES_STDOUT_HPP

#include "node.hpp"

#include <iostream>

namespace Nodes
{

class StdOut : public Node
{

public:

	virtual Node* clone() const { return new StdOut(); }

	virtual unsigned getInputsSize() const
	{
		return 1;
	}

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		(void)outputs;
		Values const& values = inputs[0];
		for (unsigned i = 0; i < values.size(); ++ i) {
			std::cout << values[i].toString() << std::flush;
		}
	}
};

}

#endif
