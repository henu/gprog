#include "node.hpp"

#include "../network.hpp"

namespace Nodes
{

void Node::cloneEdges(Network const* src_network, Network* cloned_network, std::string const& src_name) const
{
	for (Edge edge : edges) {
		std::string dest_name = src_network->getNodeName(edge.dest);
		cloned_network->addEdge(src_name, dest_name, edge.src_idx, edge.dest_idx);
	}
}

}
