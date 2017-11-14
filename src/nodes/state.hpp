#ifndef NODES_STATE_HPP
#define NODES_STATE_HPP

#include "../refcounted.hpp"
#include "../sharedptr.hpp"
#include "../value.hpp"

#include <map>

namespace Nodes
{

class Node;

class State : public RefCounted
{

public:

	inline State(unsigned inputs_size, unsigned outputs_size)
	{
		inputs.assign(inputs_size, Values());
(void)outputs_size;
	}

	inline void getAndClearInputs(ValuesVec& result)
	{
		unsigned inputs_size = inputs.size();
		inputs.swap(result);
		unsigned clear_until = std::min<unsigned>(inputs_size, inputs.size());
		inputs.resize(inputs_size, Values());
		for (unsigned i = 0; i < clear_until; ++ i) {
			inputs[i].clear();
		}
	}

	inline void addToInputs(ValuesVec const& new_inputs)
	{
		if (new_inputs.size() > inputs.size()) {
			throw std::runtime_error("Got too many inputs!");
		}
		for (unsigned i = 0; i < new_inputs.size(); ++ i) {
			inputs[i].insert(inputs[i].end(), new_inputs[i].begin(), new_inputs[i].end());
		}
	}

private:

	ValuesVec inputs;
};

typedef std::map<Node const*, SharedPtr<State> > States;

}

#endif
