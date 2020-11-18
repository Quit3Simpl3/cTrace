#include "Graph.h"

#include <utility>
#include <iostream>

using namespace std;

Graph::Graph() :
    edges(vector<vector<int>>(1, vector<int>(1,0))),
    infections(vector<int>(1,0)),
    virus_free(vector<int>(0,1)),
    infected_nodes(vector<int>(0,1)),
    _infected_counter(0)
    {/*default constructor*/}

Graph::Graph(std::vector<std::vector<int>> matrix) :
    edges(vector<vector<int>>(1, vector<int>(1,0))),
    infections(vector<int>(1,0)),
    virus_free(vector<int>(0,1)),
    infected_nodes(vector<int>(0,1)),
    _infected_counter(0) { // TODO: Any way to use the default constructor's initializer list?
    this->edges = matrix; // TODO: maybe use move constructor?
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
    this->infected_nodes.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    return (this->infections[nodeInd]==1);
}

bool Graph::isVirusFree(int nodeInd) {
    int edges_size = this->edges.size();
    if (nodeInd >= 0 && nodeInd < edges_size) {
        return (this->virus_free[nodeInd]==1);
    }
    return false;
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

vector<int> Graph::getNeighbors(int node) {
    int edges_size = 0; // Set a default size to edges_size for safety
    edges_size = this->edges[node].size();
    vector<int> neighbors = vector<int>(edges_size, -1); // initialize neighbors vector for safety
    for (int i = 0; i < edges_size; ++i) {
        if (this->edges[node][i] == 1) neighbors[i] = i;
    }
    return neighbors;
}

int Graph::getInfectedCounter() const {
    return this->_infected_counter;
}

void Graph::_setInfectedCounter(int val) {
    this->_infected_counter = val;
}

void Graph::_infectedCounterUp() {
    int count = this->getInfectedCounter() + 1;
    this->_setInfectedCounter(count);
}

std::vector<std::vector<int>> Graph::getEdges() {
    return this->edges;
}

std::vector<int> Graph::getInfectedNodes() {
    return this->infected_nodes;
}

Graph::Graph(const Graph *other) :
        edges(other->edges),
        infections(other->infections),
        virus_free(other->virus_free),
        infected_nodes(other->infected_nodes),
        _infected_counter(other->_infected_counter) {}