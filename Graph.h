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
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    
    int size();
    vector<int> getegde(int k);
    
private:
    std::vector<std::vector<int>> edges;
    std::vector<InfectionState> nodes_state;
    int infected_counter;
};

#endif