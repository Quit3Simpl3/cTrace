#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>
#include "Tree.h"

using namespace std;
using namespace nlohmann;

vector<vector<int>> json_to_adjacency_matrix(json j) {
    vector<vector<int>> matrix = j.at("graph");
    return matrix;
}

void Session::json_to_agents(json j) {
    // reset _active_viruses to 0:
    this->_setActiveViruses(0);
    vector<pair<string, int>> agents_matrix = j.at("agents");
    for (const pair<string, int>& a : agents_matrix) {
        this->createAgent(a.first, a.second); // create the necessary agent
    }
}

void Session::createAgent(const string& agent_type, int start_node) {
//    Agent* agent;
    if (agent_type == "C" || agent_type == "c") {
//        agent = new ContactTracer(); // create a new contactTracer agent
        this->addAgent(ContactTracer());
    }
    else {
//        agent = new Virus(start_node); // create a new Virus agent
        this->activeVirusesUp(); // update active viruses counter
        this->addAgent(Virus(start_node));
        this->g.occupyNode(start_node); // mark start_node as occupied
    }
//    this->addAgent(*agent); // add the new agent to the agents vector
    // TODO: make sure everything is deleted
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

bool Session::checkStopCondition() { // check termination conditions
    Graph* graph = this->getGraph();
    return (
            (graph->getInfectedCounter() == graph->size())
            ||
            (this->getActiveViruses() == 0)
            );
}

void Session::updateCycle() {
    this->cycle++;
}

void Session::simulate() {
    cout << "Starting simulation..." << endl;
    int i = 0;
    do {
        // create tmp_agents vector -> run foreach-loop over tmp_agents
        vector<Agent*> tmp_agents(this->agents);
        for (auto agent : tmp_agents) { // iterate over all active agents
            agent->act(*this); // if a new virus has been added during this cycle, do not 'act' it until the new cycle
        }
        this->updateCycle(); // cycle++
        // DEBUG
        i++;
        // DEBUG
    }
    while(!this->checkStopCondition() || i == 9);
    json answer;
    answer["graph"] = this->getGraph()->getEdges();
    answer["infected"] = this->getGraph()->getInfectedNodes();
    ofstream myAnserIs("./output.json");
    myAnserIs << answer;
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

Graph* Session::getGraph() {
    Graph* ptr_g = &(this->g);
    return ptr_g;
}

    int Session::getCycle() const  {
    return this->cycle;
}

void Session::activeVirusesUp() {
    this->_setActiveViruses(this->_active_viruses+1);
}

void Session::activeVirusesDown() {
    this->_setActiveViruses(this->_active_viruses-1);
}

int Session::getActiveViruses() const {
    return this->_active_viruses;
}

void Session::_setActiveViruses(int val) {
    this->_active_viruses = val;
}
