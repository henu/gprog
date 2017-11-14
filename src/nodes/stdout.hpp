#ifndef NODES_STDOUT_HPP
#define NODES_STDOUT_HPP

#include "node.hpp"
#include "../value.hpp"

namespace Nodes
{

class StdOut : public Node
{

public:

	virtual unsigned getInputsSize() const
	{
		return 1;
	}

private:

};

}

#endif
