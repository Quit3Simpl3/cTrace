#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

class Agent; // DO NOT CHANGE!

enum TreeType{ // DO NOT CHANGE!
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session();
    Session(const std::string& path); // DO NOT CHANGE!

    void simulate(); // DO NOT CHANGE!
    void addAgent(const Agent& agent); // DO NOT CHANGE!
    void setGraph(const Graph& graph); // DO NOT CHANGE!
    
    void enqueueInfected(int); // DO NOT CHANGE!
    int dequeueInfected(); // DO NOT CHANGE!
    TreeType getTreeType() const; // DO NOT CHANGE!
    Graph getGraph();
    int getCycle();

private:
    Graph g; // DO NOT CHANGE!
    TreeType treeType; // DO NOT CHANGE!
    std::vector<Agent*> agents; // DO NOT CHANGE!
    std::vector<std::vector<int>> matrix;
    queue<int> infectedQ;
    bool checkStopCondition();
    void updateCycle();
    void createViruses(const vector<int>& nodes);
    void createContactTracers(int contact_tracers);
    int cycle;
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