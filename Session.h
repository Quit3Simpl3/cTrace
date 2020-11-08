#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session();
    Session(const std::string& path);
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    Graph getGraph() const;
    int getcyclenum () const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector<std::vector<int>> matrix;
    int cyclenum;
};

#endif

/*
class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
}
 */