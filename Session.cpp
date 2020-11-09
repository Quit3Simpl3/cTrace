#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>
#include "Tree.h"

using namespace std;
using namespace nlohmann;

vector<vector<int>> json_to_matrix(json j) {
    vector<vector<int>> matrix = j.at("graph");

    return matrix;
}

vector<int> json_to_viruses(json j) {
    vector<int> viruses;
    for (int i = 0; i < j.at("agents").size(); ++i) {
        if (j.at("agents").at(i)[0] == "V") {
            viruses.push_back(j.at("agents").at(i)[1]);
        }
    }

    return viruses;
}

int json_to_tracers(json j) {
    int contact_tracers = 0;
    for (int i = 0; i < j.at("agents").size(); ++i) {
        if (j.at("agents").at(i) == "C") {
            contact_tracers++;
        }
    }

    return contact_tracers;
}

TreeType json_to_treeType(json j) {
    string tree_type_short = j.at("tree");
    if (tree_type_short == "M") return MaxRank;
    if (tree_type_short == "C") return Cycle;
    else return Root; // maybe if(..."R")?
}

Session::Session() { // default constructor - is this REALLY necessary?

}

Session::Session(const std::string &path) {
    // read json from file and parse to vertices adjacency matrix
    fstream stream(path);
    json j;
    stream >> j;
    Graph g = Graph(json_to_matrix(j));
    setGraph(g);
    this->matrix = matrix;

    // parse json to viruses:
    vector<int> viruses = json_to_viruses(j);
    // todo: create agents from viruses

    // parse json to contact tracers:
    int contact_tracers = json_to_tracers(j);
    // todo: create agents from contact_tracers

    // set treeType from json:
    this->treeType = json_to_treeType(j);


    cyclenum = 0;  //TODO: need to think if this is the right place for it
}

void Session::simulate() {
    cout << this->matrix.size() << endl;
    cout << "Starting simulation..." << endl;
    Tree *t = Tree :: BFS(*this,0);
    int answer = t->traceTree();
    cout<<answer<<endl;
}

void Session::addAgent(const Agent& agent) {
    // todo: add agent to this->agents
}

void Session::setGraph(const Graph &graph) {
    this->g = graph; // todo: check move-constructor
}

void Session::enqueueInfected(int) {
    // TODO
}

int Session::dequeueInfected() {
    return 0; // TODO
}

TreeType Session::getTreeType() const {
    return this->treeType;
}

Graph Session::getGraph() const {
    return Graph(this->g);
}

int Session::getcyclenum() const{
    return cyclenum;
}
