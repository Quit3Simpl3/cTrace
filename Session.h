#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "json.hpp"

using namespace nlohmann;

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
    Graph* getGraph();
    int getCycle();
    void json_to_agents(json j);

private:
    Graph g; // DO NOT CHANGE!
    TreeType treeType; // DO NOT CHANGE!
    std::vector<Agent*> agents; // DO NOT CHANGE!
    queue<int> infectedQ;
    bool checkStopCondition();
    void updateCycle();
    void createAgent(int contact_tracers);
    int cycle;
};

#endif