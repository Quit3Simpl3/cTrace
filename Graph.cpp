#include "Graph.h"

#include <utility>
#include <iostream>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    cout << "I'm gonna start building your graph now..." << endl; // delme
    this->edges = std::move(matrix); // rename matrix to this.edges
    int num_of_nodes = this->edges.size();
    this->nodes_state = vector<InfectionState>(num_of_nodes, VirusFree);
    /*for (int i = 0; i < num_of_nodes; ++i) {
        this->nodes_state.push_back(VirusFree); // virus-free, infected, occupied // TODO: maybe without vector?
    }*/
    this->infected_counter = 0; // no vertices are currently infected
}

void Graph::infectNode(int nodeInd) {
    this->nodes_state[nodeInd] = Infected; // set node as infected
    this->infected_counter++; // Update infected_counter
}

bool Graph::isInfected(int nodeInd) {
    return (this->nodes_state[nodeInd] == 1);
}

Graph::Graph() {
    //TODO: do we really need a default constructor?
}

int Graph::size() const {
    return (this->edges.size());
}

vector<int> Graph::getegde(int k) const {
    return edges[k];
}

void Graph::removeEdge(int u, int v) { // remove the edge {u,v} from this->edges
    this->edges[u][v] = 0; // removes the edge from u's neighbors list
    this->edges[v][u] = 0; // removes the edge from v's neighbors list
}
