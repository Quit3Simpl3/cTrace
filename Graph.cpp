#include "Graph.h"

#include <utility>
#include <iostream>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    cout << "I'm gonna start building your graph now..." << endl; // delme
    this->edges = matrix; // rename matrix to this.edges
    this->infections = vector<int>(this->edges.size(), 0);
    this->virus_free = vector<int>(this->edges.size(), 1);
    this->_setInfectedCounter(0); // no vertices are currently infected
}

void Graph::occupyNode(int nodeInd) {
    this->virus_free[nodeInd] = 0;
}

void Graph::infectNode(int nodeInd) {
    this->infections[nodeInd] = 1;
    this->_infectedCounterUp(); // Update infected_counter
}

bool Graph::isInfected(int nodeInd) {
    return (this->infections[nodeInd]==1);
}

bool Graph::isVirusFree(int nodeInd) {
    return (this->virus_free[nodeInd]==1);
}

Graph::Graph() {/* default constructor */}

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

vector<int> Graph::getNeighbors(int node) {
    vector<int> neighbors;
    for (int i = 0; i < this->edges[node].size(); ++i) { // TODO: don't iterate if no neighbors
        if (this->edges[node][i] == 1) neighbors.push_back(i);
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

std::vector<std::vector<int>> Graph::getedges() {
    return edges;
}

std::vector<int> Graph::getinfections() {
    vector<int> myinfectons;
    for (int i = 0; i<this->size(); i++){
        if (infections[i] == 1)
            myinfectons.push_back(i);
    }
    return myinfectons;
}
