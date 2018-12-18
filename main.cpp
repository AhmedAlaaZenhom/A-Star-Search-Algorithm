#include <iostream>
#include<bits/stdc++.h>

using namespace std;
#define INF 999

struct Node
{
    char name ;
    int hValue ;
    bool isVisited ;
    vector<pair <Node* , int> > adjacentNodes ; // Vector of adjacent nodes to a node, with the cost for going to each of them.

    int currentCostFromSrc ;

    Node *currentVia ; // The parent node this node, this parent node may be the source node, or a node in 1 step back node to the source node from the current node

    Node(char name , int hValue){ // constructor to the node
        this->name = name ;
        this->hValue = hValue ;
        this->isVisited = false ;
        this->currentCostFromSrc = INF ;
    }
};
class Graph // Graph is the grid containing bunch of connected nodes
{
	vector<Node*> graphNodes ;

	char destName ;

	int currentBestCostToDest = INF;

public:

    void addNode(Node *node){ // Adding node to the graphNodes vector
	    graphNodes.push_back(node);
    }

	void addEdge(Node *src , Node *dest , int cost){ // adding a route or edge by Adding dest to src's vector and Adding src to dest's vector.
	    (*src).adjacentNodes.push_back(make_pair(dest,cost)) ;
	    (*dest).adjacentNodes.push_back(make_pair(src,cost)) ;
    }

    void startAStarSearch(Node *src , Node *dest){ // publi function to start the heuristic search from, by defining your destination and your goal.
        this->destName = (*dest).name ;
        if((*src).name == destName){
            cout<<"You're already there"<<endl ;
            return ;
        }
        // it's obvious y3ni :"D , cost of src to source is 0 , and a src has no parent node
        (*src).currentCostFromSrc = 0 ;
        (*src).currentVia = nullptr ;

        aStarSearch() ;

        printPath(dest) ; // after the search is done, we shall print the path
    }

private:

    void aStarSearch(){ // the main function for the A* search
	    Node *leastNode = nullptr ;
	    int lowestCostFromSrc = INF ;
        for(int i=0 ;i<graphNodes.size() ;i++){ // we loop over all available nodes on our graph
            if(!(*graphNodes[i]).isVisited // if the current node is not visited before
               && (*graphNodes[i]).currentCostFromSrc < currentBestCostToDest // if the accumulated path cost to this cost is not larger than the cost to an already found path (if found)
               && (*graphNodes[i]).currentCostFromSrc + (*graphNodes[i]).hValue < lowestCostFromSrc){ // by this clause we find the next least heuristic node to expand

                   lowestCostFromSrc = (*graphNodes[i]).currentCostFromSrc + (*graphNodes[i]).hValue ;
                   leastNode = graphNodes[i] ;
            }
        }
        if(leastNode!=nullptr){ // if we really found a node to expand
            //cout<<"Expanding Node " <<(*leastNode).name<<endl ;
            (*leastNode).isVisited = true ; // here we flag this node to be visited
            expandNode(leastNode,(*leastNode).currentCostFromSrc) ; // expand this node
            aStarSearch() ; // recursively  call aStarSearch again
        }
    }

    void expandNode(Node *node,int costFromSrc){ // the function to expand a node
        for(int i=0 ; i<(*node).adjacentNodes.size() ; i++){ // looping over all the adjacent nodes to this node
            Node *adjacentNode  = (*node).adjacentNodes[i].first ;
            if((*adjacentNode).isVisited){ // if an adjacent node is visited skip it
                continue ;
            }
            int combinedCost = costFromSrc + (*node).adjacentNodes[i].second ; // cost to the current node to be expanded + the cost of the path from this node to the current adjacent node
            if((*adjacentNode).currentCostFromSrc > combinedCost){ // if the calculated path to the adjacent node is less than the current calculated path cost to it (if found), then update it and the Via value of it
                (*adjacentNode).currentCostFromSrc = combinedCost ;
                (*adjacentNode).currentVia = node ; // setting the current node as the best current parent to this adjacent node
            }
            if((*adjacentNode).name==this->destName){ // if we reached the goal at any time
                currentBestCostToDest = (*adjacentNode).currentCostFromSrc ; // update the current best path cost to teh goal
                //cout<<(*adjacentNode).name<<" Destination Reached with last updated cost: "<<(*adjacentNode).currentCostFromSrc<<endl ;
            }
        }
    }

    void printPath(Node *dest){ // function to print the cost
        cout<<"Path from source to destination is:"<<endl ;
        vector<char> charVector ;
        while(dest!=nullptr){ // looping from destination to it's parent to it's parent to it's parent ..... etc till we reach the source.
            charVector.push_back((*dest).name) ;
            dest = (*dest).currentVia ;
        }
        for(int i=charVector.size()-1 ; i>=0 ;i--){ // printing the vector upside down
            cout<<charVector[i]<<" " ;
        }
        cout<<endl<<"With a cost of "<<currentBestCostToDest<<endl ;
    }

};

int main()
{
    Graph g;
    Node A('A',10) ;
    Node B('B',8) ;
    Node C('C',5) ;
    Node D('D',7) ;
    Node E('E',3) ;
    Node F('F',6) ;
    Node G('G',5) ;
    Node H('H',3) ;
    Node I('I',1) ;
    Node J('J',0) ;

    g.addNode(&A) ;
    g.addNode(&B) ;
    g.addNode(&C) ;
    g.addNode(&D) ;
    g.addNode(&E) ;
    g.addNode(&F) ;
    g.addNode(&G) ;
    g.addNode(&H) ;
    g.addNode(&I) ;
    g.addNode(&J) ;

    g.addEdge(&A,&B,6) ;
    g.addEdge(&A,&F,3) ;
    g.addEdge(&B,&D,2) ;
    g.addEdge(&B,&C,3) ;
    g.addEdge(&C,&D,1) ;
    g.addEdge(&C,&E,5) ;
    g.addEdge(&D,&E,8) ;
    g.addEdge(&E,&I,5) ;
    g.addEdge(&E,&J,5) ;
    g.addEdge(&F,&G,1) ;
    g.addEdge(&F,&H,7) ;
    g.addEdge(&G,&I,3) ;
    g.addEdge(&H,&I,2) ;
    g.addEdge(&I,&J,3) ;

    g.startAStarSearch(&A,&J) ;

    return 0;
}
