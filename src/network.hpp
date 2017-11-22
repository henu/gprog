#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "json.hpp"
#include "nodes/node.hpp"
#include "nodes/state.hpp"
#include "sharedptr.hpp"

#include <map>

class Network
{

public:

	Network();
	Network(JSON const& json);

	void clear();

	void setNode(std::string const& node_name, Nodes::Node* node);

	void addEdge(std::string const& src, std::string const& dest, unsigned src_idx = 0, unsigned dest_idx = 0);

	Nodes::Node const* getNode(std::string const& node_name) const;

	// For iterating nodes
	std::string getFirstNodeName() const;
	std::string getNextNodeName(std::string const& node_name) const;

	// Called by NetworkState
	void createNodeStates(Nodes::States& nodestates) const;

private:

	typedef std::map<std::string, SharedPtr<Nodes::Node> > NodeMap;

	NodeMap nodes;
};

#endif
