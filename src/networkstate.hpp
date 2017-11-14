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

	void run();

private:

	Network const* net;

	Nodes::States nodes;

	Nodes::ConstNodeSet active_nodes;
};

#endif
