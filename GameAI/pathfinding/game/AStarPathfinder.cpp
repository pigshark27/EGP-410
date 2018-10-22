#include "AStarPathfinder.h"
#include "PriorityQueue.h"
#include "Compare.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Vector2D.h"
#include "Game.h"
#include "GameApp.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>


using namespace std;

AStarPathfinder::AStarPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

AStarPathfinder::~AStarPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	PriorityQueue <Node*, std::vector<Node*>, Compare> nodesToVisit;
	nodesToVisit.push(pFrom);

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	//create Path
	Path* pPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.top();
		//remove node from list
		nodesToVisit.pop();
		//add Node to Path
		pPath->addNode(pCurrentNode);

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();


			if (!toNodeAdded && !pPath->containsNode(pTempToNode) && nodesToVisit.find(pTempToNode) == nodesToVisit.end())
			{
				//update node data
				pTempToNode->backPointer = pCurrentNode->getId();
				pTempToNode->weight = pConnection->getCost() + pCurrentNode->weight;
				pTempToNode->heurWeight = pTempToNode->weight + heuristicGenerator(pTempToNode, pTo);

				nodesToVisit.push(pTempToNode);//push and sort in Priority Queue
				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	/* //uncomment and fix
   delete(pPath);
   Path* fPath = new Path();
   while (pCurrentNode != pFrom) {
	   Node* thisNode = mpGraph->getNode(pCurrentNode->backPointer);
	   fPath->addNode(thisNode);
	   pCurrentNode = thisNode;
   }
   mpPath = fPath;// path that's visualized?
   // */
	mpPath = pPath; // delete

#endif
	return pPath;

}

float AStarPathfinder::heuristicGenerator(Node* currentNode, Node* pTo) 
{
	Grid* pGrid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	Vector2D distVec = pGrid->getULCornerOfSquare(pTo->getId()) - pGrid->getULCornerOfSquare(currentNode->getId());
	float dist = distVec.getLength();
	return dist;
}