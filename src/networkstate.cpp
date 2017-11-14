#include "networkstate.hpp"

NetworkState::NetworkState(Network const* net) :
net(net)
{
	net->createNodeStates(nodes);

	// Activate those nodes that are initially active
	for (Nodes::States::iterator i = nodes.begin(); i != nodes.end(); ++ i) {
		Nodes::Node const* node = i->first;
		if (node->isInitiallyActive()) {
			active_nodes.insert(node);
		}
	}
}

void NetworkState::run()
{
	ValuesVec inputs;
	Nodes::ValuesVecsByNode outputs;

	while (!active_nodes.empty()) {

		// Go active nodes through
		for (Nodes::Node const* node : active_nodes) {
			Nodes::State* state = nodes[node].get();

			// Get inputs and run
			state->getAndClearInputs(inputs);
			node->run(inputs, outputs);
		}

		// Use outputs to active new nodes
		active_nodes.clear();
		for (Nodes::ValuesVecsByNode::iterator i = outputs.begin(); i != outputs.end(); ++ i) {
			Nodes::Node const* node = i->first;
			Nodes::State* state = nodes[node].get();
			// Store outputs as inputs
			ValuesVec const& values = i->second;
			state->addToInputs(values);
			// This node is active during next frame
			active_nodes.insert(node);
		}

		outputs.clear();
	}
}
