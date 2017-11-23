#ifndef NETWORKSTATE_HPP
#define NETWORKSTATE_HPP

#include "network.hpp"
#include "nodes/node.hpp"
#include "nodes/state.hpp"

#include <set>

class NetworkState
{

public:

	NetworkState(Network const* net);

	void run(unsigned long max_steps = 0);

	Nodes::State const* getState(Nodes::Node const* node) const;

private:

	Network const* net;

	Nodes::States nodes;

	Nodes::ConstNodeSet active_nodes;
};

#endif
