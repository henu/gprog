#include "network.hpp"

#include "nodefactory.hpp"
#include "nodes/and.hpp"
#include "nodes/conditional_constant.hpp"
#include "nodes/conditional_forward.hpp"
#include "nodes/constant.hpp"
#include "nodes/delay.hpp"
#include "nodes/is_value.hpp"
#include "nodes/not.hpp"
#include "nodes/or.hpp"
#include "nodes/splitter.hpp"
#include "nodes/stdin.hpp"
#include "nodes/stdout.hpp"
#include "nodes/xor.hpp"

Network::Network()
{
}

Network::Network(JSON const& json)
{
	// Create default nodes
	nodes["stdout"] = new Nodes::StdOut();
	nodes["stdin"] = new Nodes::StdIn();

	NodeFactory::Factories factories = NodeFactory().getFactories();

	// Read nodes
	JSON const& nodes_json = json.get("nodes");
	for (std::string node_name = nodes_json.firstKey(); nodes_json.contains(node_name); node_name = nodes_json.nextKey(node_name)) {
		JSON const& node_json = nodes_json.get(node_name);
		std::string node_type = node_json.get("type").getString();

		Nodes::Node* node = NULL;
		for (unsigned i = 0; i < factories.size(); ++ i) {
			NodeFactory::Factory const& factory = factories[i];
			if (factory.name == node_type) {
				// Read arguments
				Values node_args;
				for (unsigned j = 0; j < factory.args.size(); ++ j) {
					NodeFactory::Argument const& arg = factory.args[j];
					if (node_json.contains(arg.name)) {
						node_args.push_back(Value(node_json.get(arg.name)));
					} else if (!arg.optional) {
						throw std::runtime_error("Node \"" + node_name + "\" of type " + node_type + " is missing argument \"" + arg.name + "\"!");
					}
				}
				node = factory.func(node_args);
				break;
			}
		}
		if (node == NULL) {
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
		std::string src_name;
		unsigned src_idx;
		if (src_json.isString()) {
			src_name = src_json.getString();
			src_idx = 0;
		} else {
			src_name = src_json.get(0).getString();
			src_idx = src_json.get(1).getInteger();
		}
		NodeMap::iterator nodes_find = nodes.find(src_name);
		if (nodes_find == nodes.end()) {
			throw std::runtime_error("Unknown edge source \"" + src_name + "\"!");
		}
		Nodes::Node* src = nodes_find->second.get();

		// Get destination node
		std::string dest_name;
		unsigned dest_idx;
		if (dest_json.isString()) {
			dest_name = dest_json.getString();
			dest_idx = 0;
		} else {
			dest_name = dest_json.get(0).getString();
			dest_idx = dest_json.get(1).getInteger();
		}
		nodes_find = nodes.find(dest_name);
		if (nodes_find == nodes.end()) {
			throw std::runtime_error("Unknown edge destination \"" + dest_name + "\"!");
		}
		Nodes::Node* dest = nodes_find->second.get();

		src->addEdgeTo(dest, src_idx, dest_idx);
	}
}

SharedPtr<Network> Network::clone() const
{
	SharedPtr<Network> clone = new Network();
	// First clone nodes without edges
	for (auto i : nodes) {
		clone->nodes[i.first] = i.second->clone();
	}
	// Then clone edges
	for (auto i : nodes) {
		std::string src = i.first;
		i.second->cloneEdges(this, clone.get(), i.first);
	}
	return clone;
}

void Network::clear()
{
	nodes.clear();
}

void Network::setNode(std::string const& node_name, Nodes::Node* node)
{
	nodes[node_name] = node;
}

void Network::addEdge(std::string const& src, std::string const& dest, unsigned src_idx, unsigned dest_idx)
{
	NodeMap::iterator src_find = nodes.find(src);
	if (src_find == nodes.end()) {
		throw std::runtime_error("Node \"" + src + "\" not found!");
	}
	NodeMap::iterator dest_find = nodes.find(dest);
	if (dest_find == nodes.end()) {
		throw std::runtime_error("Node \"" + dest + "\" not found!");
	}
	src_find->second->addEdgeTo(dest_find->second.get(), src_idx, dest_idx);
}

Nodes::Node const* Network::getNode(std::string const& node_name) const
{
	NodeMap::const_iterator nodes_find = nodes.find(node_name);
	if (nodes_find == nodes.end()) {
		return NULL;
	}
	return nodes_find->second.get();
}

std::string Network::getNodeName(Nodes::Node* node) const
{
	for (auto i : nodes) {
		if (i.second.get() == node) {
			return i.first;
		}
	}
	throw std::runtime_error("Node could not be found!");
}

std::string Network::getFirstNodeName() const
{
	if (nodes.empty()) return "";
	return nodes.begin()->first;
}

std::string Network::getNextNodeName(std::string const& node_name) const
{
	NodeMap::const_iterator nodes_find = nodes.upper_bound(node_name);
	if (nodes_find == nodes.end()) return nodes.rbegin()->first + "_";
	return nodes_find->first;
}

void Network::createNodeStates(Nodes::States& nodestates) const
{
	for (NodeMap::const_iterator i = nodes.begin(); i != nodes.end(); ++ i) {
		Nodes::Node* node = i->second.get();
		Nodes::State* state = new Nodes::State(node);
		nodestates[node] = state;
	}
}
