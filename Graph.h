#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

enum InfectionState{
    VirusFree,
    Infected,
    Occupied
};

class Graph{
public:
    Graph(); // TODO: Make sure we REALLY need a default constructor
    Graph(std::vector<std::vector<int>> matrix); // DO NOT CHANGE!

    void infectNode(int nodeInd); // DO NOT CHANGE!
    bool isInfected(int nodeInd); // DO NOT CHANGE!
    
    int size() const;
    vector<int> getegde(int k) const;
    
private:
    std::vector<std::vector<int>> edges; // DO NOT CHANGE!
    std::vector<InfectionState> nodes_state;
    int infected_counter;
};

#endif