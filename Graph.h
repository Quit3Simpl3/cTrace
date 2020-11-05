#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    int size();
    vector<int> getegde(int k);
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> nodes_state;
    int infected_counter;
};

#endif
