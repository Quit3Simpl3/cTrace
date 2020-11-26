#include "Tree.h"
#include <queue>
#include <vector>
#include "Session.h"
#include <array>
#include <typeinfo>
#include <iostream>

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children() {}

void Tree::addChild(const Tree &child) { // addChile copies child
    char type = child.getType();
    if (type == 'C') {
        Tree* kid = new CycleTree((CycleTree&)child);
        this->children.push_back(kid);
    }
    else if (type == 'M') {
        Tree* kid = new MaxRankTree((MaxRankTree&)child);
        this->children.push_back(kid);
    }
    else {
        Tree* kid = new RootTree((RootTree&)child);
        this->children.push_back(kid);
    }
}

void Tree::addChild(Tree* child) { // mover
    this->children.push_back(child);
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    if(type == MaxRank) return (new MaxRankTree(rootLabel));
    if (type == Cycle) return (new CycleTree(rootLabel, session.getCycle()));
    return (new RootTree(rootLabel));
}

Tree *Tree::BFS(Session& session, int rootLabel) {
    Graph* g = session.getGraph();
    queue <Tree*> child_pos;  // for running the BFS
    vector<bool> is_child_in_children(g->size(), true); // to know if the node is in the tree. initialize all vector items to 'true'

    Tree *father_tree = Tree::createTree(session, rootLabel);
    Tree *tmptree;
    child_pos.push(father_tree);
    is_child_in_children[rootLabel] = false; // so that we don't use the same child twice
    do {
        tmptree = child_pos.front(); // starting with father_tree
        child_pos.pop();
        const vector<int>& node_edges = g->getEdge(tmptree->getNode());
        int node_edges_size = node_edges.size();
        for (int i = 0; i < node_edges_size; ++i) {
            if (node_edges[i] == 1 && is_child_in_children[i]) {
                is_child_in_children[i] = false; // so that we don't use the same child twice
                Tree *child_tree = Tree::createTree(session, i);
                child_pos.push(child_tree);
                tmptree->addChild(child_tree); // using addChild(Tree* child) - mover, not copier
            }
        }
    } while (!child_pos.empty());
    return father_tree;
}

int Tree::getNode() const { // gets rootLabel/node
    return node;
}

vector<Tree*> Tree::getChildren() {
    return children;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel) , currCycle(currCycle) {/*default constructor*/}

int CycleTree::traceTree() {
    if (currCycle == 0 || getChildren().empty()) { // return current tree
        return getNode();
    }
    else {
        Tree *cycle_round = getChildren()[0];
        for (int i = 1; !(cycle_round->getChildren().empty()) && i < currCycle; ++i) {
            cycle_round = cycle_round->getChildren()[0];
        }
        return cycle_round->getNode();
    }
}

int CycleTree::getCycle() const {
    return this->currCycle;
}

char CycleTree::getType() const {
    return 'C';
}

char MaxRankTree::getType() const {
    return 'M';
}

char RootTree::getType() const {
    return 'R';
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    if (getChildren().empty()) {
        return getNode();
    }
    else {
        vector<array<int,3>> track_tree ;// 0 = children size, 1 = high of the node, 2 = node number
        maxRankTraceTree(track_tree, 0);
        int point = 0;
        int track_tree_size = track_tree.size();
        for (int i = 1; i < track_tree_size;++i) {
            if (track_tree[i][0]>track_tree[point][0]){
                point = i;
            }
            else if (track_tree[i][0]==track_tree[point][0]){
                if(track_tree[i][1]<track_tree[point][1]) {
                    point = i;
                }
            }
        }
        return track_tree[point][2];
    }
}

void Tree::clone_children(const Tree &other) { // used in copy-constructor
    int size = other.size();
    for (int i = 0; i < size; ++i) {
        char type = other.children[i]->getType();
        // it's okay to static-cast because we're sure about the CHILD's type!
        if (type == 'C') {
            CycleTree* new_kid = new CycleTree(static_cast<CycleTree const&>(*other.children[i]));
            this->children.push_back(new_kid);
        }
        else if (type == 'M') {
            MaxRankTree* new_kid = new MaxRankTree(static_cast<MaxRankTree const&>(*other.children[i]));
            this->children.push_back(new_kid);
        }
        else {
            RootTree* new_kid = new RootTree(static_cast<RootTree const&>(*other.children[i]));
            this->children.push_back(new_kid);
        }
    }
}

Tree::Tree(const Tree &other) : node(other.node), children() { // Copy-Constructor
    this->clone_children(other);
}

MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {/*Copy-Constructor*/}

MaxRankTree::MaxRankTree(MaxRankTree &&other) : Tree(other) {/*Move-Constructor*/}

RootTree::RootTree(const RootTree &other) : Tree(other) {/*Copy-Constructor*/}

CycleTree::CycleTree(const CycleTree &other) :
    Tree(other),
    currCycle(other.getCycle()) {/*copy-constructor*/}

int Tree::size() const {
    return this->children.size();
}

void Tree::maxRankTraceTree (vector<array<int,3>> &track_tree, int high) {
    int tree_size = children.size();
    track_tree.push_back({(int)tree_size, (int)high, (int) getNode()});
    if (getChildren().empty()) {
    }
    else {
        for (int i = 0; i < tree_size; ++i) {
            children[i]->maxRankTraceTree(track_tree, high + 1);
        }
    }
}

Tree::~Tree() {
    this->clear();
}

void Tree::clear() {
    int children_size = this->children.size();
    for (int i = 0; i < children_size; ++i) { // delete this Tree's children
        delete this->children[i];
    }
    this->node = -1;
    this->children.clear();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {/*Default Constructor*/}

int RootTree::traceTree() {
    return getNode();
}

Tree::Tree(Tree &&other) : // Move-Constructor
    node(other.node),
    children(other.children) {
    other.children = vector<Tree*>();
    other.clear();
}

Tree &Tree::operator=(const Tree &other) { // Copy Assignment Operator
    if (this != &other) {
        this->clear();
        this->node = other.node;
        this->clone_children(other);
    }
    return *this;
}

Tree &Tree::operator=(Tree &&other) { // Move Assignment Operator
    if (this != &other) {
        clear();
        node = other.node;
        children = other.children;
        other.children = vector<Tree*>();
        other.clear();
    }
    return *this;
}