#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"
#include <array>
#include <typeinfo>

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) , children() {}

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
    vector<bool> is_child_in_children; // to know if the node is in the tree;

//    Graph& g = session.getGraph();
    Graph* g = session.getGraph(); // TODO: test with line 30 working

    for (int i=0;  i < g->size();++i ) { // initialize the vector
        is_child_in_children.push_back(true);
    }
    Tree *father_tree = Tree::createTree(session, rootLabel);
    Tree *tmptree;
    child_pos.push(father_tree);

    is_child_in_children[rootLabel] = false;
    do {
        tmptree = child_pos.front();
        child_pos.pop();
        const vector<int>& node_edges = g->getEdge(tmptree->getNode());
        int node_edges_size = node_edges.size();
        for (int i = 0; i < node_edges_size; ++i) {
            if (node_edges[i] == 1 && is_child_in_children[i]) {
                is_child_in_children[i] = false;
                Tree *child_tree = Tree::createTree(session,i);
                child_pos.push(child_tree);
                tmptree->addChild(*child_tree);
            }
        }

    } while (!child_pos.empty());
    return father_tree;
}

int Tree::getNode() {
    return node;
}

vector<Tree*> Tree::getChildren() {
    return children;
}


CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle) {}

int CycleTree::traceTree() {
    if (currCycle == 0 || getChildren().empty()) {
        return getNode();
    } else {
        Tree *cycle_round = getChildren()[0];
        for (int i = 1; !(cycle_round->getChildren().empty()) && i < currCycle; ++i) {
            cycle_round = cycle_round->getChildren()[0];
        }
        return cycle_round->getNode();
    }
  // TODO: trace the bfs tree
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    if (getChildren().empty()) {
        return getNode();
    }
    else {
        vector<array<int,3>> track_tree ;// 0 = children size, 1 = high of the node, 2 = node number
        maxRankTraceTree(track_tree, 0); //i will change to static
        int point = 0;
        int track_tree_size = track_tree.size();
        for (int i = 1; i < track_tree_size;++i) {
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

void Tree::maxRankTraceTree (vector<array<int,3>> &track_tree, int high) {
    int mysize = children.size();
    track_tree.push_back({(int)mysize, (int)high, (int) getNode()});
    if (getChildren().empty()) {
    } else {
        for (int i = 0; i < mysize; ++i) {
            children[i]->maxRankTraceTree(track_tree, high + 1);
        }
    }
}

Tree::~Tree() {
    this->clear();
}

Tree::Tree(const Tree &aTree) : node(aTree.node), children(aTree.children) {/*copy-constructor*/}

void Tree::clear() {
    int children_size = this->children.size();
    for (int i = 0; i < children_size; ++i) { // delete this Tree's children
        delete children[i];
    }
}

Tree &Tree::operator=(const Tree &other) {
    if (other.children == this->children) {
        return *this;
    }
    this->clear();
    this->node = other.node;
    this->children = other.children;
    return *this;
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return getNode();
}