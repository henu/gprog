#ifndef NODES_DELAY_HPP
#define NODES_DELAY_HPP

#include "node.hpp"

namespace Nodes
{

class Delay : public Nodes::Node
{

public:

	inline Delay(unsigned time = 0) : time(time) { }

	virtual unsigned getInputsSize() const { return 1; }
	virtual unsigned getOutputsSize() const { return 1; }

	virtual void* initializeStateData() const
	{
		if (time > 0) {
			StateData* data = new StateData();
			data->queue_write_pos = 0;
			data->queue.assign(time, Values());
			return data;
		}
		return NULL;
	}

	virtual void cleanStateData(void* data) const
	{
		StateData* statedata = (StateData*)data;
		delete statedata;
	}

	virtual bool isActiveWithoutInput(void const* data) const
	{
		if (time > 0) {
			StateData const* statedata = (StateData const*)data;
			for (Values const& vals : statedata->queue) {
				if (!vals.empty()) return true;
			}
		}
		return false;
	}

private:

	struct StateData
	{
		ValuesVec queue;
		unsigned queue_write_pos;
	};

	unsigned time;

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const
	{
		// Special case
		if (time == 0) {
			outputs[0] = inputs[0];
			return;
		}

		StateData* statedata = (StateData*)state->getData();

		// Get oldest values as output
		unsigned read_pos = (statedata->queue_write_pos + time - 1) % time;
		outputs[0] = statedata->queue[read_pos];
		statedata->queue[read_pos].clear();

		// Write new inputs to queue
		statedata->queue[statedata->queue_write_pos];
		statedata->queue_write_pos = (statedata->queue_write_pos + 1) % time;
	}
};

}

#endif
