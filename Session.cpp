#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>
#include "Tree.h" // TODO: remove me?

using namespace std;
using namespace nlohmann;

json Session::_create_json(const std::string &path) {
    ifstream stream(path, ifstream::binary);
    json j;
    stream >> j;
    return j;
}

json Session::_json() {
    return this->js;
}

/*vector<vector<int>> json_to_adjacency_matrix(json j) {
    vector<vector<int>> matrix = j.at("graph");
    return matrix;
}*/

vector<vector<int>> Session::_json_to_matrix() {
    /*ifstream stream(path,ifstream::binary);

    json j;
    stream >> j; // parse json from file*/

    vector<vector<int>> matrix = this->_json().at("graph"); //j.at("graph");
    return matrix;
}

/*void Session::json_to_agents(json j) {
    // reset _active_viruses to 0:
    this->_setActiveViruses(0);
    vector<pair<string, int>> agents_matrix = j.at("agents");
    for (const pair<string, int>& a : agents_matrix) {
        this->createAgent(a.first, a.second); // create the necessary agent
    }
}*/

void Session::_json_to_agents(json j) {
    // reset _active_viruses to 0:
    this->_setActiveViruses(0);
    vector<pair<string, int>> agents_matrix = j.at("agents");
    for (const pair<string, int>& a : agents_matrix) {
        this->createAgent(a.first, a.second); // create the necessary agent
    }
}

void Session::createAgent(const string& agent_type, int start_node) {
    if (agent_type == "C" || agent_type == "c") {
        this->addAgent(ContactTracer());
    }
    else {
        this->activeVirusesUp(); // update active viruses counter
//        Virus* virus = new Virus(start_node);
        this->addAgent(Virus(start_node));
        this->g.occupyNode(start_node); // mark start_node as occupied
    }
    // TODO: make sure temp ct and virus are deleted
}

void Session::addAgent(const Agent& agent) { // DO NOT CHANGE SIGNATURE
    if (agent.getType() == 'V') {
        Virus* virus = new Virus(agent.getNode());
        this->agents.push_back(virus);
    }
    else {
        ContactTracer* contact_tracer = new ContactTracer();
        this->agents.push_back(contact_tracer);
    }
}

TreeType json_to_treeType(json j) {
    string tree_type_short = j.at("tree");
    if (tree_type_short == "M") return MaxRank;
    if (tree_type_short == "C") return Cycle;
    else return Root; // maybe if(..."R")?
}

Session::Session(const std::string &path) :
    js(_create_json(path)),
    g(Graph(_json_to_matrix())),
    treeType(json_to_treeType(this->js)),
    agents(),
    _active_viruses(0),
    infectedQ(),
    cycle(0) // reset cycle to 0
    {
    // Add agents to Session by their order in json config file:
    this->_json_to_agents(this->js); // parse json to agents

    // set treeType from json:
    /*this->treeType = json_to_treeType(this->js);*/
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
    do {
        // create tmp_agents vector -> run foreach-loop over tmp_agents
        vector<Agent*> tmp_agents(this->agents);
        for (auto agent : tmp_agents) { // iterate over all active agents
            agent->act(*this); // if a new virus has been added during this cycle, do not 'act' it until the new cycle
        }
        this->updateCycle(); // cycle++
    } while(!this->checkStopCondition());

    json output;
    output["graph"] = this->getGraph()->getEdges();
    output["infected"] = this->getGraph()->getInfectedNodes();
    ofstream output_stream("./output.json");
    output_stream << output;
}

void Session::setGraph(const Graph &graph) {
    this->g = &graph; // using Copy-Constructor because &graph is const
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

Session::~Session() {
    int agents_size = this->agents.size();
    for (int i = 0; i < agents_size; ++i) {
        delete this->agents[i];
    }
    clearQ(this->infectedQ);
}

void Session::clearQ(queue<int>& q) {
    queue<int> empty;
    swap(q, empty);
}
