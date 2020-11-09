#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"


using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) , children() {

}

void Tree::addChild(const Tree &child)  {
    children.push_back((Tree*) (&child));
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Session temp = session; //need to fix the syntax..
    if(temp.getTreeType() == MaxRank) {
            return (new MaxRankTree(rootLabel));
   } else if (temp.getTreeType() == Cycle) {
            return (new CycleTree(rootLabel,session.getcyclenum()));
    }else
            return (new RootTree(rootLabel));
}

Tree *Tree::BFS(const Session& session, int rootLabel) {
    queue <Tree*> child_pos;  //for running the BFS
    vector<bool> child_is_in; // to know if the node is in the tree;

    const Graph& g = session.getGraph();

    for (int i=0;  i < g.size();++i ) { //initialization the vector
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

vector<Tree *> Tree::mychild() {
    return children;
}


CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle) {


}

int CycleTree::traceTree() {
    if(currCycle == 0 || mychild().empty()) {
        return mynode();
    } else {
        Tree *cycle_round = mychild()[0];
        for (int i = 0; !(cycle_round->mychild().empty())&& i < currCycle; ++i) {
            Tree *cycle_round = cycle_round->mychild()[0];
        };
        return cycle_round->mynode();
    }
    ; // TODO: trace the bfs tree
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}

int MaxRankTree::traceTree() {

    if (mychild().empty()) {
        return mynode();
    }else {
        vector<int [3]> track_tree;
                MaxtraceTree(track_tree,0); //i will change to static
        int point = 0;
        for (int i = 1; i<track_tree->size();++i) {
            if (track_tree[i][0]>track_tree[point][0]){
                point = i;
            }else if (track_tree[i][0]==track_tree[point][0]){
                if(track_tree[i][1]<track_tree[point][1]) {
                    point = i;
                }
            }
        }
        return track_tree[point][2];
        }
}
void Tree::MaxtraceTree (vector<int [3]> &track_tree, int high) {
    int mysize = children.size();
    track_tree.push_back({mysize, high, mynode()});
    if (mychild().empty()) {
        return;
    } else {
      for (int i = 0; i < mysize; ++i) {
        children[i]->MaxtraceTree(track_tree, high + 1);
        }
      return;
    }
}


RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return mynode();

}
