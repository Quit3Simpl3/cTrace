#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"


using namespace std;

Tree::Tree(int rootLabel) {
    this->node = rootLabel;
}

void Tree::addChild(const Tree &child)  {
    children.push_back((Tree*) (&child));
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Session temp = session; //need to fix the syntax..
    if(temp.getTreeType() == MaxRank) {
            return (new MaxRankTree(rootLabel));
   } else if (temp.getTreeType() == Cycle) {
            return (new CycleTree(rootLabel,rootLabel));
    }else
            return (new RootTree(rootLabel));
}

Tree *Tree::BFS(const Session& session, int rootLabel) {
    queue <Tree*> child_pos;  //for running the BFS
    vector<bool> child_is_in; // to know if the node is in the tree;

    const Graph& g = session.getGraph(); //need to fix the syntax..

    int node_size = g.size();
    for (int i=0;  i < node_size;++i ) { //initialization the vector
        child_is_in.push_back(true);
    }
    Tree *father_tree = Tree::createTree(session, rootLabel);
    Tree *tmptree;
    child_pos.push(father_tree);

    child_is_in[rootLabel] = false;
    do {
        tmptree = child_pos.front();
        child_pos.pop();
        const vector<int>& is_edge = g.getegde(tmptree->mynode());
        for (int i = 0; i < is_edge.size(); ++i) {
            if (is_edge[i] == 1 & child_is_in[i] == true) {
                child_is_in[i] = false;
                Tree *child_tree = Tree::createTree(session,i);
                child_pos.push(child_tree);
                tmptree->addChild(*child_tree);
            }
        }

    }
    while (!child_pos.empty());
    return father_tree;
}

int Tree::mynode() {
    return node;
}


CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle) {


}

int CycleTree::traceTree() {
    return 0; // TODO: trace the bfs tree
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}

int MaxRankTree::traceTree() {

    return 0;
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return 0;
}
