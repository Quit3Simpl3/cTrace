#include "Graph.h"

#include <utility>
#include <iostream>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    cout << "I'm gonna start building your graph now..." << endl; // delme
    this->edges = matrix; // rename matrix to this.edges
    this->nodes_state = vector<InfectionState>(this->edges.size(), VirusFree);
    this->_setInfectedCounter(0); // no vertices are currently infected
}

void Graph::occupyNode(int nodeInd) {
    this->nodes_state[nodeInd] = Occupied;
}

void Graph::infectNode(int nodeInd) {
    this->nodes_state[nodeInd] = Infected; // set node as infected
    this->_infectedCounterUp(); // Update infected_counter
}

bool Graph::isInfected(int nodeInd) {
    return (this->nodes_state[nodeInd] == Infected);
}

Graph::Graph() {
    //TODO: do we really need a default constructor?
}

int Graph::size() const {
    return (this->edges.size());
}

vector<int> Graph::getEdge(int k) const {
    return edges[k];
}

void Graph::removeEdge(int u, int v) { // remove the edge {u,v} from this->edges
    this->edges[u][v] = 0; // removes the edge from u's neighbors list
    this->edges[v][u] = 0; // removes the edge from v's neighbors list
}

bool Graph::isVirusFree(int nodeInd) {
    return (this->nodes_state[nodeInd] == VirusFree);
}

vector<int> Graph::getNeighbors(int node) {
    vector<int> neighbors;
    for (int i : this->edges[node]) {
        if (i == 1) neighbors.push_back(i);
    }
    return neighbors;
}

int Graph::getInfectedCounter() const {
    return this->_infected_counter;
}

void Graph::_setInfectedCounter(int val) {
    this->_infected_counter = val;
}

void Graph::_infectedCounterDown() {
    int count = this->getInfectedCounter() - 1;
    this->_setInfectedCounter(count);
}

void Graph::_infectedCounterUp() {
    int count = this->getInfectedCounter() + 1;
    this->_setInfectedCounter(count);
}
