#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	int backPointer = 0;
	float weight = 0;
	float heurWeight = 0;


private:
	const NODE_ID mId;
};