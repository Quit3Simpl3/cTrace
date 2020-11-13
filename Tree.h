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

    virtual ~Tree(); // Destructor

    static Tree* createTree(const Session& session, int rootLabel); // DO NOT CHANGE!
    virtual int traceTree()=0; // DO NOT CHANGE!
    static Tree* BFS(Session& session, int rootLabel);
    int getNode() const;
    vector<Tree*> getmychildren();
//    vector<Tree*> copyChildren() const;
    vector<Tree*> getKids() const;
    void MaxtraceTree(vector<array<int,3>> &track_tree, int high);

    virtual Tree* clone() const=0;

private:
    int node; // DO NOT CHANGE!
    std::vector<Tree*> children; // DO NOT CHANGE!
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!

    //CycleTree(const CycleTree* &tree); // Copy-Constructor

    virtual CycleTree* clone() const; // for copying
private:
    int currCycle; // DO NOT CHANGE!
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!

    virtual MaxRankTree* clone() const; // for copying
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
    RootTree(const RootTree& tree);

    void setChildren(std::vector<Tree*> c);

    virtual RootTree* clone() const; // for copying
};

#endif