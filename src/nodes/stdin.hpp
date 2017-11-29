#ifndef NODES_STDIN_HPP
#define NODES_STDIN_HPP

#include "node.hpp"

#include <iostream>
#include <cstdio>
#include <unistd.h>

namespace Nodes
{

class StdIn : public Node
{

public:

	virtual Node* clone() const { return new StdIn(); }

	virtual unsigned getOutputsSize() const { return 1; }

	virtual bool isActiveWithoutInput(void const* data) const
	{
		(void)data;
		return std::cin.good() && !isatty(fileno(stdin));
	}

	virtual bool isInitiallyActive() const { return true; }

private:

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		(void)state;
		(void)inputs;

		// If terminal, then give up
		if (isatty(fileno(stdin))) {
			return;
		}

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
