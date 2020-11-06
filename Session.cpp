#include "Session.h"
#include "json.hpp"
#include <fstream>

using namespace std;
using namespace nlohmann;

Session::Session(const std::string &path) {
    fstream stream(path);
    json j;
    stream >> j;
    vector<vector<int>> matrix;
    json j_graph = j.at("graph");
    for (int i = 0; i < j_graph.size(); ++i) {
        vector<int> v = j_graph.at(i); // TODO: move/copy-constructor???
        matrix.push_back(v);
    }
    this->setGraph(new Graph(json.parse_to_vector("path")["graph"]));

    this->treeType = ;
    this->agents = ;
}

void Session::simulate() {

}

void Session::addAgent(const Agent &agent) {

}

void Session::setGraph(const Graph &graph) {
    this->g = graph;
}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {
    return 0;
}

TreeType Session::getTreeType() const {

    return Root;
}

Graph Session::getgraph() {
    return Graph(g);
}
