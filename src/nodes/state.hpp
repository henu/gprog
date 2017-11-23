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

	State(Node const* node);
	virtual ~State();

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

	inline void const* getData() const { return data; }

	// Called by Node and NetworkState
	inline void* getData() { return data; }

private:

	Node const* node;

	ValuesVec inputs;

	void* data;
};

typedef std::map<Node const*, SharedPtr<State> > States;

}

#endif
