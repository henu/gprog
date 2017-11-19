#ifndef NODES_STDIN_HPP
#define NODES_STDIN_HPP

#include "node.hpp"

#include <iostream>

namespace Nodes
{

class StdIn : public Node
{

public:

	virtual unsigned getOutputsSize() const { return 1; }

	virtual bool isActiveWithoutInput(void const* data) const
	{
		(void)data;
		return std::cin.good();
	}

	virtual bool isInitiallyActive() const { return true; }

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		(void)inputs;

		// Read some data from std::cin
		unsigned const BUF_SIZE = 10000;
		char buf[BUF_SIZE];
		std::cin.read(buf, BUF_SIZE);
		unsigned buf_read = std::cin.gcount();
		std::string data(buf, buf + buf_read);

		if (!data.empty()) {
			outputs[0].push_back(Value(data));
		}
	}
};

}

#endif
