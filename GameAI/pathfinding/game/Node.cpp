#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID)
{
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	backPointer = 0;
	weight = 0;
	heurWeight = 0;
}

Node::~Node()
{
}