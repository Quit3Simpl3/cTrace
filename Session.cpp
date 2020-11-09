#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>

using namespace std;
using namespace nlohmann;

vector<vector<int>> json_to_adjacency_matrix(json j) {
    vector<vector<int>> matrix = j.at("graph");
    return matrix;
}

void Session::json_to_agents(json j) {
    vector<pair<string, int>> agents_matrix = j.at("agents");
    cout << "agents_matrix.size() = " << agents_matrix.size() << endl;
    for (int i = 0; i < agents_matrix.size(); ++i) {
        this->createAgent(agents_matrix[i].second);
    }
    /*for (pair<string, int> a : agents_matrix) {
        this->createAgent(a.second); // create the necessary agent
    }*/
}

void Session::createAgent(int start_node) {
    Agent* agent;
    if (start_node == -1) {
        agent = new ContactTracer(); // create a new contactTracer agent
    }
    else {
        agent = new Virus(start_node); // create a new Virus agent
        this->g.occupyNode(start_node); // mark start_node as occupied
    }
    this->addAgent(*agent); // add the new agent to the agents vector
}

TreeType json_to_treeType(json j) {
    string tree_type_short = j.at("tree");
    if (tree_type_short == "M") return MaxRank;
    if (tree_type_short == "C") return Cycle;
    else return Root; // maybe if(..."R")?
}

Session::Session() {/*default constructor*/}

Session::Session(const std::string &path) {
    // read json from file and parse to vertices adjacency matrix
    fstream stream(path);
    json j;
    stream >> j;
    setGraph(Graph(json_to_adjacency_matrix(j)));

    // Add agents to Session by their order in json config file:
    this->json_to_agents(j); // parse json to agents

    // set treeType from json:
    this->treeType = json_to_treeType(j);
    // reset cycle to 0:
    this->cycle = 0;
}

bool Session::checkStopCondition() {
    return false;
}

void Session::updateCycle() {
    this->cycle++;
}

void Session::simulate() {
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
    this->agents.push_back(agent.clone());
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
