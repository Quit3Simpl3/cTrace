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
    void occupyNode(int nodeInd);
    bool isVirusFree(int nodeInd);
    vector<int> getNeighbors(int node);
    int getInfectedCounter() const;

    int size() const;
    vector<int> getEdge(int k) const;

    void removeEdge(int u, int v);
    
private:
    std::vector<std::vector<int>> edges; // DO NOT CHANGE!
    std::vector<InfectionState> nodes_state;
    void _infectedCounterUp();
    void _infectedCounterDown();
    void _setInfectedCounter(int val);
    int _infected_counter;
};

#endif