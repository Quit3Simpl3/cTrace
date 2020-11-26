#include "iostream"
#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include "Agent.h"
#include <fstream>
#include "Tree.h"

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

vector<vector<int>> Session::_json_to_matrix() {
    vector<vector<int>> matrix = this->_json().at("graph");
    return matrix;
}

void Session::_json_to_agents(json j) {
    this->_setActiveViruses(0); // reset active-viruses to 0
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
        this->addAgent(Virus(start_node));
        this->g.occupyNode(start_node); // mark start_node as occupied
    }
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
    if (tree_type_short == "M" || tree_type_short == "m") return MaxRank;
    if (tree_type_short == "C" || tree_type_short == "c") return Cycle;
    else return Root;
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
    // parse json to agents and add them to Session by their order in json config file:
    this->_json_to_agents(this->js);
}

bool Session::checkStopCondition() { // check termination conditions
    Graph* graph = this->getGraph();
    return (
            (graph->getInfectedCounter() == graph->size()) /* All nodes are infected. */
            ||
            (this->getActiveViruses() == 0) /* All viruses stopped spreading. */
            );
}

void Session::updateCycle() {
    this->cycle++;
}

void Session::simulate() {
    do {
        vector<Agent*> tmp_agents(this->agents); // run for-loop on current agents, not including those added in 'act'
        for (auto agent : tmp_agents) { // iterate over all active agents
            agent->act(*this); // if a new virus has been added during this cycle, do not 'act' it until the new cycle
        }
        this->updateCycle(); // cycle++
    } while(!this->checkStopCondition());

    // Generate output.json:
    json output;
    output["graph"] = this->getGraph()->getEdges();
    output["infected"] = this->getGraph()->getInfectedNodes();
    ofstream output_stream("./output.json");
    output_stream << output;
}

void Session::setGraph(const Graph &graph) {
    this->g = Graph(graph); // using Copy-Constructor because &graph is const
}

void Session::enqueueInfected(int node) {
    this->infectedQ.push(node);
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
    this->clear();
}

void Session::clear() {
    int agents_size = this->agents.size();
    for (int i = 0; i < agents_size; ++i) {
        delete this->agents[i];
    }
    clearQ(this->infectedQ);
    g = Graph();
    this->agents = vector<Agent*>(); // To delete the pointers in agents
}

void Session::clearQ(queue<int>& q) {
    queue<int> empty;
    swap(q, empty);
}

Session::Session(const Session &other) : // Copy-Constructor
    js(json(other.js)),
    g(Graph(other.g)),
    treeType(other.getTreeType()),
    agents(),
    _active_viruses(other.getActiveViruses()),
    infectedQ(),
    cycle(other.getCycle()) {
    // Copy agents:
    int other_agents_size = other.getAgentsSize();
    for (int i = 0 ; i < other_agents_size ; ++i) {
        // copy all agents
        if (other.agents[i]->getType() == 'V') {
            Virus* virus = new Virus(other.agents[i]->getNode());
            agents.push_back(virus);
        }
        else {
            ContactTracer* contact_tracer = new ContactTracer();
            agents.push_back(contact_tracer);
        }
    }
    // Copy infected queue:
    infectedQ = copy_queue(other.infectedQ);
}

queue<int> Session::copy_queue(const queue<int> &other) {
    queue<int> new_queue = other;
    return new_queue;
}

Session::Session(Session &&other) : // Move-Constructor
    js(json(other.js)),
    g(Graph(other.g)),
    treeType(other.getTreeType()),
    agents(),
    _active_viruses(other.getActiveViruses()),
    infectedQ(),
    cycle(other.getCycle()) {
    other.js = json();
    other.g = Graph();
    // Move agents:
    int other_agents_size = other.getAgentsSize();
    for (int i = 0; i < other_agents_size; ++i) {
        agents.push_back(other.agents[i]);
        other.agents[i] = nullptr;
    }
    // Move queue and clear other's:
    infectedQ = other.infectedQ;
    clearQ(other.infectedQ);
    other.clear();
}

Session &Session::operator=(const Session &other) {
    if (this != &other) {
        clear();
        js = other.js;
        g = other.g;
        treeType = other.treeType;
        _active_viruses = other._active_viruses;
        cycle = other.cycle;
        // Copy agents:
        int other_agents_size = other.getAgentsSize();
        for (int i = 0; i < other_agents_size; ++i) {
            // copy all agents
            if (other.agents[i]->getType() == 'V') {
                Virus* virus = new Virus(other.agents[i]->getNode());
                agents.push_back(virus);
            }
            else {
                ContactTracer* contact_tracer = new ContactTracer();
                agents.push_back(contact_tracer);
            }
        }
        infectedQ = copy_queue(other.infectedQ);
    }
    return *this;
}

Session &Session::operator=(Session &&other) {
    if (this != &other) {
        this->clear();
        js = other.js;
        g = other.g;
        treeType = other.getTreeType();
        _active_viruses = other.getActiveViruses();
        cycle = other.getCycle();
        infectedQ = other.infectedQ;
        agents = other.agents;

        other.infectedQ = queue<int>();
        other.agents = vector<Agent*>();
        other.clear();
    }
    return *this;
}

int Session::getAgentsSize() const {
    return agents.size();
}

Agent *Session::getAgent(int i) {
    return this->agents[i];
}