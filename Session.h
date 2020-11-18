#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include <fstream>
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
//    Session(){}; // default constructor
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
    int getActiveViruses() const; // return count of active viruses
    void activeVirusesUp();
    void activeVirusesDown();

private:
    json js;
    Graph g; // DO NOT CHANGE!
    TreeType treeType; // DO NOT CHANGE!
    std::vector<Agent*> agents; // DO NOT CHANGE!
    int _active_viruses; // active viruses counter
    queue<int> infectedQ;
    int cycle; // cycle counter
    // private methods:
    static json _create_json(const std::string &path);
    json _json();
    void updateCycle(); // cycle++
    vector<vector<int>> _json_to_matrix();
    void _json_to_agents(json j); // parse json to agents and create them
    void _setActiveViruses(int val); // set value for _active_viruses
    bool checkStopCondition(); // checks whether termination conditions are fulfilled
    void createAgent(const string&, int); // create a new agent from json using ("V/C", node_number) pair
    static void clearQ(queue<int>& q);
};

#endif