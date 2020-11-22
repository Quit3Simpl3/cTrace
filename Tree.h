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
    Tree(const Tree &other); // Copy-Constructor
    Tree(Tree &&other); // Move-Constructor
    Tree & operator=(const Tree &other); // Copy-Assignment Operator
    Tree & operator=(Tree &&other); // Move-Assignment Operator

    static Tree* createTree(const Session& session, int rootLabel); // DO NOT CHANGE!
    virtual int traceTree()=0; // DO NOT CHANGE!

    static Tree* BFS(Session& session, int rootLabel);
    int getNode() const; // Return this->node
    vector<Tree*> getChildren();
    void maxRankTraceTree(vector<array<int,3>> &track_tree, int high);
    virtual ~Tree(); // Destructor
    virtual char getType() const=0;
    int getCycle() const { return -1; };
    int size() const;
    void clone_children(const Tree &other);

private:
    int node; // DO NOT CHANGE!
    std::vector<Tree*> children; // DO NOT CHANGE!
    void clear();
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
    CycleTree(const CycleTree &other); // Copy-Constructor
    char getType() const;
    int getCycle() const;
    CycleTree & operator=(const CycleTree &other)=default; // Copy-Assignment Operator
    CycleTree & operator=(CycleTree &&other)=default; // Move-Assignment Operator
private:
    int currCycle; // DO NOT CHANGE!
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
    MaxRankTree(const MaxRankTree &other); // Copy-Constructor
    char getType() const;
    MaxRankTree(MaxRankTree &&other);

    MaxRankTree & operator=(const MaxRankTree &other)=default; // Copy-Assignment Operator
    MaxRankTree & operator=(MaxRankTree &&other)=default; // Move-Assignment Operator
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel); // DO NOT CHANGE!
    virtual int traceTree() ; // DO NOT CHANGE!
    RootTree(const RootTree &other); // Copy-Constructor
    char getType() const;
    RootTree & operator=(const RootTree &other)=default; // Copy-Assignment Operator
    RootTree & operator=(RootTree &&other)=default; // Move-Assignment Operator
};

#endif