#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#include "state.hpp"
#include "../refcounted.hpp"
#include "../value.hpp"

#include <set>
#include <stdexcept>
#include <string>

namespace Nodes
{

typedef std::set<Nodes::Node const*> ConstNodeSet;
typedef std::map<Nodes::Node const*, ValuesVec> ValuesVecsByNode;

class Node : public RefCounted
{

public:

	virtual ~Node() { }

	inline void addEdgeTo(Node* dest, unsigned src_idx, unsigned dest_idx)
	{
		if (dest_idx >= dest->getInputsSize()) {
			throw std::runtime_error("Destination node has no input #" + std::to_string(dest_idx));
		}
		if (src_idx >= getOutputsSize()) {
			throw std::runtime_error("Source node has no output #" + std::to_string(src_idx));
		}
		edges.insert(Edge(dest, src_idx, dest_idx));
	}

	virtual unsigned getInputsSize() const { return 0; }
	virtual unsigned getOutputsSize() const { return 0; }

	// Called by State
	virtual void* initializeStateData() const { return NULL; }
	virtual void cleanStateData(void* data) const { (void)data; }

	// Called by NetworkState
	virtual bool isActiveWithoutInput(void const* data) const
	{
		(void)data;
		return false;
	}

	// Called by NetworkState
	virtual bool isInitiallyActive() const { return false; }

	// Called by NetworkState
	void run(State* state, ValuesVec const& inputs, Nodes::ValuesVecsByNode& all_outputs) const
	{
		ValuesVec node_outputs(getOutputsSize(), Values());
		doRunning(state, inputs, node_outputs);
		for (unsigned output_i = 0; output_i < node_outputs.size(); ++ output_i) {
			Values const& output = node_outputs[output_i];
			if (output.size() > 2) {
				throw std::runtime_error("Too many values in output #" + std::to_string(output_i));
			}
			if (!output.empty()) {
				Value const& value = output[0];
				for (Edge const& edge : edges) {
					if (edge.src_idx == output_i) {
						Nodes::ValuesVecsByNode::iterator all_outputs_find = all_outputs.find(edge.dest);
						ValuesVec* dest_inputs;
						if (all_outputs_find != all_outputs.end()) {
							dest_inputs = &all_outputs_find->second;
						} else {
							all_outputs[edge.dest] = ValuesVec();
							dest_inputs = &all_outputs[edge.dest];
						}
						while (dest_inputs->size() <= edge.dest_idx) {
							dest_inputs->push_back(Values());
						}
						(*dest_inputs)[edge.dest_idx].push_back(value);
					}
				}
			}
		}
	}

private:

	struct Edge
	{
		Node* dest;
		unsigned src_idx;
		unsigned dest_idx;

		inline Edge(Node* dest, unsigned src_idx, unsigned dest_idx) :
		dest(dest),
		src_idx(src_idx),
		dest_idx(dest_idx)
		{
		}

		inline bool operator<(Edge const& e) const
		{
			if (dest < e.dest) return true;
			if (dest > e.dest) return false;
			if (src_idx < e.src_idx) return true;
			if (src_idx > e.src_idx) return false;
			return dest_idx < e.dest_idx;
		}
	};
// TODO: Replace with map, where keys are output indexes!
	typedef std::set<Edge> Edges;

	Edges edges;

	virtual void doRunning(State* state, ValuesVec const& inputs, ValuesVec& outputs) const = 0;
};

}

#endif
