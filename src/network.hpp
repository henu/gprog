#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "json.hpp"
#include "nodes/node.hpp"
#include "sharedptr.hpp"

#include <map>

class Network
{

public:

	Network(JSON const& json);

private:

	typedef std::map<std::string, SharedPtr<Nodes::Node> > NodeMap;

	NodeMap nodes;
};

#endif
