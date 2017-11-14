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

	Network(JSON const& json);

	// Called by NetworkState
	void createNodeStates(Nodes::States& nodestates) const;

private:

	typedef std::map<std::string, SharedPtr<Nodes::Node> > NodeMap;

	NodeMap nodes;
};

#endif
