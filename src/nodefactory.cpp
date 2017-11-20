#include "nodefactory.hpp"

#include "nodes/and.hpp"
#include "nodes/conditional_constant.hpp"
#include "nodes/conditional_forward.hpp"
#include "nodes/constant.hpp"
#include "nodes/delay.hpp"
#include "nodes/is_value.hpp"
#include "nodes/not.hpp"
#include "nodes/or.hpp"
#include "nodes/splitter.hpp"
#include "nodes/xor.hpp"

NodeFactory::NodeFactory()
{
	Factory and_factory;
	and_factory.name = "and";
	and_factory.func = createAnd;
	factories.push_back(and_factory);

	Factory conditional_constant_factory;
	conditional_constant_factory.name = "conditional_constant";
	conditional_constant_factory.func = createConditionalConstant;
	conditional_constant_factory.args.push_back(Argument("value"));
	factories.push_back(conditional_constant_factory);

	Factory conditional_forward_factory;
	conditional_forward_factory.name = "conditional_forward";
	conditional_forward_factory.func = createConditionalForward;
	factories.push_back(conditional_forward_factory);

	Factory constant_factory;
	constant_factory.name = "constant";
	constant_factory.func = createConstant;
	constant_factory.args.push_back(Argument("value"));
	factories.push_back(constant_factory);

	Factory delay_factory;
	delay_factory.name = "delay";
	delay_factory.func = createDelay;
	delay_factory.args.push_back(Argument("time", true));
	factories.push_back(delay_factory);

	Factory is_value_factory;
	is_value_factory.name = "is_value";
	is_value_factory.func = createIsValue;
	is_value_factory.args.push_back(Argument("value"));
	factories.push_back(is_value_factory);

	Factory not_factory;
	not_factory.name = "not";
	not_factory.func = createNot;
	factories.push_back(not_factory);

	Factory or_factory;
	or_factory.name = "or";
	or_factory.func = createOr;
	factories.push_back(or_factory);

	Factory splitter_factory;
	splitter_factory.name = "splitter";
	splitter_factory.func = createSplitter;
	factories.push_back(splitter_factory);

	Factory xor_factory;
	xor_factory.name = "xor";
	xor_factory.func = createXor;
	factories.push_back(xor_factory);
}

Nodes::Node* NodeFactory::createAnd(Values const& args)
{
	(void)args;
	return new Nodes::And();
}

Nodes::Node* NodeFactory::createConditionalConstant(Values const& args)
{
	return new Nodes::ConditionalConstant(args[0]);
}

Nodes::Node* NodeFactory::createConditionalForward(Values const& args)
{
	(void)args;
	return new Nodes::ConditionalForward();
}

Nodes::Node* NodeFactory::createConstant(Values const& args)
{
	return new Nodes::Constant(args[0]);
}

Nodes::Node* NodeFactory::createDelay(Values const& args)
{
	if (args.size() >= 1) return new Nodes::Delay(args[0].toInteger());
	return new Nodes::Delay();
}

Nodes::Node* NodeFactory::createIsValue(Values const& args)
{
	return new Nodes::IsValue(args[0]);
}

Nodes::Node* NodeFactory::createNot(Values const& args)
{
	(void)args;
	return new Nodes::Not();
}

Nodes::Node* NodeFactory::createOr(Values const& args)
{
	(void)args;
	return new Nodes::Or();
}

Nodes::Node* NodeFactory::createSplitter(Values const& args)
{
	(void)args;
	return new Nodes::Splitter();
}

Nodes::Node* NodeFactory::createXor(Values const& args)
{
	(void)args;
	return new Nodes::Xor();
}
