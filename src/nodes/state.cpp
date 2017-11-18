#include "state.hpp"

#include "node.hpp"

namespace Nodes
{

State::State(Node const* node) :
node(node)
{
	inputs.assign(node->getInputsSize(), Values());
	data = node->initializeStateData();
}

State::~State()
{
	node->cleanStateData(data);
}

}
