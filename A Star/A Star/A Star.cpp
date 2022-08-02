// A Star.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class AStarPaths
{
    string node1;
    string node2;
    int pathWeight;

public:
    AStarPaths(string _node1, string _node2, int _pathWeight) :
        node1(_node1), node2(_node2), pathWeight(_pathWeight)
    {}

    //Check if either of the nodes in the path are the ones passed
    //If true, returns the opposite node passed.
    //If false, returns empty string
    string PathCheck(string nodeBeginning)
    {
        if (node1 == nodeBeginning)
            return node2;
        if (node2 == nodeBeginning)
            return node1;
        return "";
    }
    int GetPathWeight() { return pathWeight; }
};

class AStarTracking
{
    string node;
    AStarTracking * previousNode;
    int totalWeight;
    int pathOnlyWeight;

public:
    AStarTracking(string _node, int _totalWeight, int _pathOnlyWeight, AStarTracking* _previousNode = nullptr) :
        node(_node), totalWeight(_totalWeight), pathOnlyWeight(_pathOnlyWeight), previousNode(_previousNode)
    {}

    AStarTracking() :
        node("a"), totalWeight(0), pathOnlyWeight(0), previousNode(nullptr)
    {}

    string GetNode() const{ return node; }
    int GetWeight() const { return totalWeight; }
    AStarTracking* GetPrevPointer() const { return previousNode; }


    //returns true if values were changed
    bool NodeCompare(AStarTracking * prevNode, int addedWeight)
    {
        if (prevNode->pathOnlyWeight + addedWeight < totalWeight)
        {
            pathOnlyWeight = prevNode->pathOnlyWeight + addedWeight;
            totalWeight = prevNode->pathOnlyWeight + addedWeight;
            previousNode = prevNode;
            return true;
        }
        return false;
    }

    void BranchPaths(vector<AStarPaths>& pathList, vector<AStarTracking *>& nodeList, vector<AStarTracking*>& completedNodeList)
    {
        vector<AStarPaths>::iterator pathIter = pathList.begin();
        vector<AStarTracking *>::iterator nodeIter;

        string nodeCross;
        int pathWeight;
        //goes through every pathway the node is attached to
        for (; pathIter != pathList.end(); ++pathIter)
        {
            //check if the path if this node is involved in the path
            //returns blank otherwise
            nodeCross = pathIter->PathCheck(node);
            if (nodeCross == "")
                continue;
            pathWeight = pathIter->GetPathWeight();

            bool replacedNode = false;
            nodeIter = nodeList.begin();
            for (; nodeIter != nodeList.end(); ++nodeIter)
            {
                //Looks for the node in the list if it has a weight waiting
                if ((*nodeIter)->GetNode() == nodeCross)
                {
                    //if the existing node has a lower weight, replace the node's weight and previous node
                    (*nodeIter)->NodeCompare(this, pathWeight);
                    replacedNode = true;
                    break;
                }
            }
            //If the node wasn't found, make sure it wasn't previously created before
            if (!replacedNode)
            {
                nodeIter = completedNodeList.begin();
                for (; nodeIter != completedNodeList.end(); ++nodeIter)
                {
                    //Looks for the node in the list if it has a weight waiting
                    if ((*nodeIter)->GetNode() == nodeCross)
                    {
                        //if the existing node has a lower weight, replace the node's weight and previous node
                        if((*nodeIter)->NodeCompare(this, pathWeight))
                            nodeList.push_back(*nodeIter);//readd the node back into the nodelist
                        replacedNode = true;
                        break;
                    }
                }
            }
            //if a node wasn't found in the list, create a new node
            //Its okay if the node has been put in the completed list before and a new node is created instead
            //the path back uses a reverse linked list
            if (!replacedNode)
            {
                AStarTracking* newNode = new AStarTracking(nodeCross, pathOnlyWeight + pathWeight, pathOnlyWeight + pathWeight, this);
                nodeList.push_back(newNode);
            }
        }

        //Remove the node from the node iterator to completedList
        nodeIter = nodeList.begin();
        for (; nodeIter != nodeList.end(); ++nodeIter)
        {
            if ((*nodeIter)->GetNode() == node)
            {
                completedNodeList.push_back(*nodeIter);
                nodeList.erase(nodeIter);
                break;
            }
        }
    }

    bool operator < (const AStarTracking& rhs) const
    {
        return (totalWeight < rhs.GetWeight());
    }
};

bool PointerAStarTrackingComparison(AStarTracking * lhs, AStarTracking * rhs) { return (*lhs < *rhs); }

void PrintPath(AStarTracking * node)
{
    cout << "Path to the end: ";
    string pathString;
    while (node != nullptr)
    {
        pathString = node->GetNode() + " " + pathString;
        node = node->GetPrevPointer();
    }
    cout << pathString << endl;
}

void DeleteVectorValues(vector<AStarTracking*>& list)
{
    vector<AStarTracking*>::iterator nodeIter;
    while (!list.empty())
    {
        delete list.back();
        list.pop_back();
    }
}

void GetToEndAStar(vector<AStarPaths> & pathList)
{
    vector<AStarTracking*> nodeList;
    vector<AStarTracking*> completedNodeList;

    nodeList.push_back(new AStarTracking());

    bool endFound = false;
    while (!nodeList.empty())
    {

        //sorts the list
        sort(nodeList.begin(), nodeList.end(), PointerAStarTrackingComparison);

        if (nodeList[0]->GetNode() == "end")
        {
            endFound = true;
            break;
        }

        nodeList[0]->BranchPaths(pathList, nodeList, completedNodeList);
    }

    if (endFound)
        PrintPath(nodeList[0]);
    else
        cout << "No Path Found" << endl;

    DeleteVectorValues(nodeList);
    DeleteVectorValues(completedNodeList);
}

int main()
{
    vector<AStarPaths> pathList;
    pathList.push_back(AStarPaths("a", "b", 5));
    pathList.push_back(AStarPaths("b", "c", 1));
    pathList.push_back(AStarPaths("a", "end", 7));
    pathList.push_back(AStarPaths("c", "end", 1));

    GetToEndAStar(pathList);

    std::cout << "Hello World!\n";
}