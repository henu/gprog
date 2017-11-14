#include "network.hpp"

#include "nodes/constant.hpp"
#include "nodes/stdout.hpp"

Network::Network(JSON const& json)
{
	// Create default nodes
	nodes["stdout"] = new Nodes::StdOut();

	// Read nodes
	JSON const& nodes_json = json.get("nodes");
	for (std::string node_name = nodes_json.firstKey(); nodes_json.contains(node_name); node_name = nodes_json.nextKey(node_name)) {
		JSON const& node_json = nodes_json.get(node_name);
		std::string node_type = node_json.get("type").getString();

		Nodes::Node* node;

		if (node_type == "constant") {
			JSON const& data = node_json.get("data");
			if (data.isString()) {
				node = new Nodes::Constant(data.getString());
			} else {
				throw std::runtime_error("Node \"" + node_name + "\" has unsupported data!");
			}
		} else {
			throw std::runtime_error("Unsupported node type \"" + node_type + "\"!");
		}

		nodes[node_name] = node;
	}

	// Read edges
	JSON const& edges_json = json.get("edges");
	for (unsigned i = 0; i < edges_json.size(); ++ i) {
		JSON const& edge_json = edges_json.get(i);

		JSON const& dest_json = edge_json.get(1);

		// Get source node
		JSON const& src_json = edge_json.get(0);
		Nodes::Node* src;
		unsigned src_idx;
		if (src_json.isString()) {
			src = nodes[src_json.getString()].get();
			src_idx = 0;
		} else {
			src = nodes[src_json.get(0).getString()].get();
			src_idx = src_json.get(1).getInteger();
		}

		// Get destination node
		Nodes::Node* dest;
		unsigned dest_idx;
		if (dest_json.isString()) {
			dest = nodes[dest_json.getString()].get();
			dest_idx = 0;
		} else {
			dest = nodes[dest_json.get(0).getString()].get();
			dest_idx = dest_json.get(1).getInteger();
		}

		src->addEdgeTo(dest, src_idx, dest_idx);
	}
}
