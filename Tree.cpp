#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"

using namespace std;

Tree::Tree(int rootLabel) {
    this->node = rootLabel;
  //  Tree first_child = new Tree(rootLabel);
  //  children.push_back()
}

void Tree::addChild(const Tree &child)  {
    Tree* pointer = (Tree*) (&child);
    children.push_back(pointer);
}


Tree *Tree::createTree(const Session &session, int rootLabel) {
    Session temp = session; //need to fix the sintex..
    //if(temp.getTreeType() == MaxRank) { //need to fix
    //    Tree *max_tree = new MaxRankTree(rootLabel);
  //  }
    queue <int> child_pos;  //for running the BFS
    vector<bool> child_is_in; // to know if the node is in the tree;


    Graph tempgraph = temp.getgraph(); //need to fix the sintex..
    int node_size = tempgraph.size();
    for (int i=0;  i < node_size;++i ) { //initialization the vector
        child_is_in[i] = true;
    }
    child_pos.push(rootLabel);
    Tree *father_tree = new MaxRankTree(rootLabel);
    child_is_in[rootLabel] == false;
    while (!child_pos.empty()) {
        int tmp_node = child_pos.front();
        child_pos.pop();
        vector<int> is_edge = tempgraph.getegde(tmp_node);
        for (int i = 0; i < node_size; ++i){
            if (is_edge[i] == 1 & child_is_in[i] == true) {
                child_is_in[i] == false;
                child_pos.push(i);
                Tree *max_tree_child = new MaxRankTree(i);
                father_tree->addChild(*max_tree_child);
            }

        }

    }








    return nullptr;
}

int Tree::BFS(TreeType type,int rootLabel) {


    return 0;
}


CycleTree::CycleTree(int rootLabel, int currCycle) {

}

int CycleTree::traceTree() {
    return 0;
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
