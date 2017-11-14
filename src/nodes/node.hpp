#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#include "../refcounted.hpp"

#include <set>
#include <stdexcept>
#include <string>

namespace Nodes
{

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

	virtual unsigned getInputsSize() const
	{
		return 0;
	}

	virtual unsigned getOutputsSize() const
	{
		return 0;
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
	typedef std::set<Edge> Edges;

	Edges edges;
};

}

#endif
