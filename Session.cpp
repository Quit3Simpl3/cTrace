#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>

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
    vector<int> virus_nodes = json_to_viruses(j);
    this->createViruses(virus_nodes);

    // parse json to contact tracers:
    int contact_tracers = json_to_tracers(j);
    this->createContactTracers(contact_tracers);

    // set treeType from json:
    this->treeType = json_to_treeType(j);
    // reset cycle to 0:
    this->cycle = 0;
}

void Session::createViruses(const vector<int>& nodes) {
    for (int node : nodes) {
        Agent* virus = new Virus(node); // create new Virus agent
        this->g.occupyNode(node);
        this->addAgent(*virus); // add the new agent to the agents vector
    }
}

void Session::createContactTracers(int contact_tracers) {
    for (int i = 0; i < contact_tracers; ++i) {
        Agent* contact_tracer = new ContactTracer(); // create new contactTracer agent
        this->addAgent(*contact_tracer); // add the new agent to the agents vector
    }
}

bool Session::checkStopCondition() {
    return false;
}

void Session::updateCycle() {
    this->cycle++;
}

void Session::simulate() {
    cout << "Number of nodes: " << this->matrix.size() << endl;
    cout << "Starting simulation..." << endl;
    //while(!this->checkStopCondition()) {
    for (int i = 0; i < 10; ++i) {
        for (auto agent : this->agents) { // iterate over all active agents
            agent->act(*this);
        }
        this->updateCycle(); // cycle++
    }
    //}
}

void Session::addAgent(const Agent& agent) {
    this->agents.push_back((Agent*)&agent); // TODO: handle deleting of agent object
}

void Session::setGraph(const Graph &graph) {
    this->g = graph; // todo: check move-constructor
}

void Session::enqueueInfected(int node) {
    this->infectedQ.push(node);
    // maybe handle graph here?
}

int Session::dequeueInfected() {
    if (this->infectedQ.empty()) { // handle empty queue
        return -1;
    }
    else {
        int node = this->infectedQ.front(); // get node at front of the queue
        infectedQ.pop(); // delete node at front of the queue
        return node;
    }
}

TreeType Session::getTreeType() const {
    return this->treeType;
}

Graph Session::getGraph() {
    return Graph(this->g); // TODO: why not 'return this->g;'?
}

int Session::getCycle() {
    return this->cycle;
}
