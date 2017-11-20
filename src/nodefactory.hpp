#ifndef NODEFACTORY_HPP
#define NODEFACTORY_HPP

#include "value.hpp"
#include "nodes/node.hpp"

#include <vector>

class NodeFactory
{

public:

	typedef Nodes::Node* (*Function)(Values const& args);

	struct Argument
	{
		std::string name;
		bool optional;
		inline Argument(std::string const& name, bool optional=false) : name(name), optional(optional) {}
	};
	typedef std::vector<Argument> Arguments;
	struct Factory
	{
		std::string name;
		Function func;
		Arguments args;
	};
	typedef std::vector<Factory> Factories;

	NodeFactory();

	inline Factories const& getFactories() const { return factories; }

private:

	Factories factories;

	static Nodes::Node* createAnd(Values const& args);
	static Nodes::Node* createConditionalConstant(Values const& args);
	static Nodes::Node* createConditionalForward(Values const& args);
	static Nodes::Node* createConstant(Values const& args);
	static Nodes::Node* createDelay(Values const& args);
	static Nodes::Node* createIsValue(Values const& args);
	static Nodes::Node* createNot(Values const& args);
	static Nodes::Node* createOr(Values const& args);
	static Nodes::Node* createSplitter(Values const& args);
	static Nodes::Node* createXor(Values const& args);
};

#endif
