#include "Graph.h"

#include <utility>

Graph::Graph(std::vector<std::vector<int>> matrix) {
    this->edges = std::move(matrix);
    /*for (int i = 0; i < edges.size(); ++i) {
        this->nodes_state[i] = 0; // 0=virus-free, 1=infected, 2=occupied
    }
    this->infected_counter = 0; // no vertices are currently infected*/
}

void Graph::infectNode(int nodeInd) {
    this->nodes_state[nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd) {
    return (this->nodes_state[nodeInd] == 1);
}

Graph::Graph() {

}
