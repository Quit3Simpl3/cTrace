#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>

using namespace std;
using namespace nlohmann;

Session::Session(const std::string &path) {
    // read json from file and parse to matrix
    fstream stream(path);
    json j;
    stream >> j;
    vector<vector<int>> matrix = j.at("graph"); // creates adjacency matrix from config JSON
    cout << matrix.size() << endl;
    this->g = Graph(matrix);
    this->matrix = matrix;
}

void Session::simulate() {
    cout << this->matrix.size() << endl;
    cout << "Starting simulation..." << endl;
}

void Session::addAgent(const Agent& agent) {
    // todo: add agent to this->agents
}

void Session::setGraph(const Graph &graph) {
    this->g = graph; // todo: check move-constructor
}
