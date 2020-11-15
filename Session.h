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
    Session(){}; // default constructor
    Session(const std::string& path); // DO NOT CHANGE!
    // TODO: implement copy-constructor of Session (deep copy of agents and graph) if needed
    virtual ~Session();

    void simulate(); // DO NOT CHANGE!
    void addAgent(const Agent& agent); // DO NOT CHANGE!
    void setGraph(const Graph& graph); // DO NOT CHANGE!
    
    void enqueueInfected(int); // DO NOT CHANGE!
    int dequeueInfected(); // DO NOT CHANGE!
    TreeType getTreeType() const; // DO NOT CHANGE!
    Graph* getGraph(); // returns pointer to Session.g
    int getCycle() const; // returns current cycle of simulation
    void json_to_agents(json j); // parse json to agents and create them
    int getActiveViruses() const; // return count of active viruses
    void activeVirusesUp();
    void activeVirusesDown();

private:
    Graph g; // DO NOT CHANGE!
    TreeType treeType; // DO NOT CHANGE!
    std::vector<Agent*> agents; // DO NOT CHANGE!
    int _active_viruses; // active viruses counter
    void _setActiveViruses(int val); // set value for _active_viruses
    queue<int> infectedQ;
    bool checkStopCondition(); // checks whether termination conditions are fulfilled
    void updateCycle(); // cycle++
    void createAgent(const string&, int); // create a new agent from json using ("V/C", node_number) pair
    int cycle; // cycle counter
    static void clearQ(queue<int>& q);
};

#endif