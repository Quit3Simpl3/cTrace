#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"
#include <array>
#include <typeinfo>


using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) , children() {

}

void Tree::addChild(const Tree &child)  {
    children.push_back((Tree*) (&child));
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    if(type == MaxRank) return (new MaxRankTree(rootLabel));
    if (type == Cycle) return (new CycleTree(rootLabel, session.getCycle()));
    return (new RootTree(rootLabel));
}

Tree *Tree::BFS(Session& session, int rootLabel) {
    queue <Tree*> child_pos;  //for running the BFS
    vector<bool> child_is_in; // to know if the node is in the tree;

//    Graph& g = session.getGraph();
    Graph* g = session.getGraph(); // TODO: test with line 30 working

    for (int i=0;  i < g->size();++i ) { //initialization the vector
        child_is_in.push_back(true);
    }
    Tree *father_tree = Tree::createTree(session, rootLabel);
    Tree *tmptree;
    child_pos.push(father_tree);

    child_is_in[rootLabel] = false;
    do {
        tmptree = child_pos.front();
        child_pos.pop();
        const vector<int>& is_edge = g->getEdge(tmptree->getmynode());
        for (int i = 0; i < is_edge.size(); ++i) {
            if (is_edge[i] == 1 & child_is_in[i] == true) {
                child_is_in[i] = false;
                Tree *child_tree = Tree::createTree(session,i);
                child_pos.push(child_tree);
                tmptree->addChild(*child_tree);
            }
        }

    } while (!child_pos.empty());
    return father_tree;
}

int Tree::getmynode() {
    return node;
}

vector<Tree *> Tree::getmychildren() {
    return children;
}


CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle) {}

int CycleTree::traceTree() {
    if (currCycle == 0 || getmychildren().empty()) {
        return getmynode();
    } else {
        Tree *cycle_round = getmychildren()[0];
        for (int i = 1; !(cycle_round->getmychildren().empty()) && i < currCycle; ++i) {
            cycle_round = cycle_round->getmychildren()[0];
        }
        return cycle_round->getmynode();
    }
  // TODO: trace the bfs tree
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    if (getmychildren().empty()) {
        return getmynode();
    }else {
        vector<array<int,3>> track_tree ;// 0 = children size, 1 = high of the node, 2 = node number
        MaxtraceTree(track_tree,0); //i will change to static
        int point = 0;
        for (int i = 1; i<track_tree.size();++i) {
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

void Tree::MaxtraceTree (vector<array<int,3>> &track_tree, int high) {
    int mysize = children.size();
    track_tree.push_back({(int)mysize, (int)high, (int)getmynode()});
    if (getmychildren().empty()) {
    } else {
        for (int i = 0; i < mysize; ++i) {
            children[i]->MaxtraceTree(track_tree, high + 1);
        }
    }
}

Tree::~Tree() {
    this->clear();
}

Tree::Tree(const Tree &aTree) : node(aTree.node)  {

    this->children = aTree.children;
}

void Tree::clear() {
   /*if (!this->children.empty()){
     this->children.clear();
   }*/
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

Tree &Tree::operator=(const Tree &k) {
    if (k.children == this->children ) {
        return *this;
    }
    this->clear();
    this->node = k.node;
    this->children = k.children;
    return *this;
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return getmynode();
}