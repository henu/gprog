#ifndef NODES_SPLITTER_HPP
#define NODES_SPLITTER_HPP

#include "node.hpp"

namespace Nodes {

class Splitter : public Node
{

public:

	virtual unsigned getInputsSize() const { return 1; }
	virtual unsigned getOutputsSize() const { return 1; }

	virtual void* initializeStateData() const
	{
		return new StateData();
	}

	virtual void cleanStateData(void* data) const
	{
		StateData* statedata = (StateData*)data;
		delete statedata;
	}

	virtual bool isActiveWithoutInput(void const* data) const
	{
		StateData const* statedata = (StateData const*)data;
		return !statedata->queue.empty();
	}

private:

	struct StateData
	{
		Values queue;
	};

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		StateData* statedata = (StateData*)state->getData();

		// First push possible new items
		for (Value value : inputs[0]) {
			// Single value cases
			if (value.isBoolean() || value.isNull() || value.isNumber()) {
				statedata->queue.push_back(value);
			}
			// Vector
			else if (value.isVector()) {
// TODO: Code this!
assert(false);
			}
			// Map
			else if (value.isMap()) {
// TODO: Code this!
assert(false);
			}
			// String
			else if (value.isString()) {
				std::string const& str = value.toString();
				if (!str.empty()) {
					statedata->queue.push_back(value);
				}
			}
		}

		// If queue is empty, then do nothing more
		if (statedata->queue.empty()) {
			return;
		}

		// Extract one item. First check special case, where oldest item is string
		if (statedata->queue[0].isString()) {
			std::string const& str = statedata->queue[0].toString();
			assert(!str.empty());
// TODO: If there is character type in the future, use it instead!
			outputs[0].push_back(Value(str.substr(0, 1)));
			if (str.size() == 1) {
				statedata->queue.erase(statedata->queue.begin());
			} else {
				statedata->queue[0] = Value(str.substr(1));
			}
		} else {
			outputs[0].push_back(statedata->queue[0]);
			statedata->queue.erase(statedata->queue.begin());
		}
	}
};

}

#endif
