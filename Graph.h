#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

enum InfectionState{
    VirusFree,
    Infected,
    Occupied
};

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

private:
    std::vector<std::vector<int>> edges;
    std::vector<InfectionState> nodes_state;
    int infected_counter;
};

#endif
