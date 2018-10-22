#pragma once
#include "Node.h"

class Compare
{
public:
	bool operator() (Node* lhs, Node* rhs) // left hand side and right hand side
	{
		return lhs->heurWeight > rhs->heurWeight; // get the weights of the nodes
	}
};