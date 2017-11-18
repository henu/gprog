#include "network.hpp"

#include "nodes/conditional_constant.hpp"
#include "nodes/conditional_forward.hpp"
#include "nodes/constant.hpp"
#include "nodes/delay.hpp"
#include "nodes/is_value.hpp"
#include "nodes/not.hpp"
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

		if (node_type == "conditional_constant") {
			if (!node_json.contains("value")) {
				throw std::runtime_error("conditional_constant node \"" + node_name + "\" is missing value!");
			}
			node = new Nodes::ConditionalConstant(Value(node_json.get("value")));
		} else if (node_type == "conditional_forward") {
			node = new Nodes::ConditionalForward();
		} else if (node_type == "constant") {
			if (!node_json.contains("value")) {
				throw std::runtime_error("constant node \"" + node_name + "\" is missing value!");
			}
			node = new Nodes::Constant(Value(node_json.get("value")));
		} else if (node_type == "delay") {
			int time = 0;
			if (node_json.contains("time")) {
				if (!node_json.get("time").isInteger()) {
					throw std::runtime_error("Delay time must be integer!");
				}
				time = node_json.get("time").getInteger();
				if (time < 0) {
					throw std::runtime_error("Delay time must be zero or greater!");
				}
			}
			node = new Nodes::Delay(time);
		} else if (node_type == "is_value") {
			if (!node_json.contains("value")) {
				throw std::runtime_error("is_value node \"" + node_name + "\" is missing value!");
			}
			node = new Nodes::IsValue(Value(node_json.get("value")));
		} else if (node_type == "not") {
			node = new Nodes::Not();
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

void Network::createNodeStates(Nodes::States& nodestates) const
{
	for (NodeMap::const_iterator i = nodes.begin(); i != nodes.end(); ++ i) {
		Nodes::Node* node = i->second.get();
		Nodes::State* state = new Nodes::State(node);
		nodestates[node] = state;
	}
}
