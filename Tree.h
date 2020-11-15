#ifndef TREE_H_
#define TREE_H_
#include "Session.h"
#include <vector>
#include <array>

using namespace std;

class Session;

class Tree{
public:
    Tree(int rootLabel); // DO NOT CHANGE!
    void addChild(const Tree &child); // DO NOT CHANGE!

    static Tree* createTree(const Session& session, int rootLabel); // DO NOT CHANGE!
    virtual int traceTree()=0; // DO NOT CHANGE!

    static Tree* BFS(Session& session, int rootLabel);
    int getNode(); // Return this->node
    vector<Tree*> getChildren();
    void maxRankTraceTree(vector<array<int,3>> &track_tree, int high);
    Tree(const Tree &aTree); // Copy-Constructor
    virtual ~Tree(); // Destructor
    Tree & operator=(const Tree &k); // Copy-Assignment Operator


private:
    int node; // DO NOT CHANGE!
    std::vector<Tree*> children; // DO NOT CHANGE!
    void clear();

};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
private:
    int currCycle; // DO NOT CHANGE!
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
};

#endif