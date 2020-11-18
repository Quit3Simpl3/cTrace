#include <iostream>
#include "Agent.h"
#include "Tree.h"

Agent::Agent() {}

ContactTracer::ContactTracer() {}

int ContactTracer::dequeueInfected(Session& session) {
    return session.dequeueInfected();
}

void ContactTracer::act(Session& session) {
    // 1) Dequeue a node from infection queue
    // 2) create BFS by TreeType from node
    // 3) use treeTrace() to get the necessary node
    // 4) remove all the node's edges

    int start_node = this->dequeueInfected(session); // get new infected node from queue
    if (start_node == -1) return; // dequeueInfected returns -1 if empty
    Tree* bfs_tree = Tree::BFS(session, start_node); // Maybe create static TraceTree() in Tree.cpp and not delete bfs_tree here?
    int patient = bfs_tree->traceTree();
    this->removeAllEdges(session, patient); // remove all the patient's edges
    delete bfs_tree; // We must delete bfs_tree
}

void ContactTracer::removeAllEdges(Session& session, int node) {
    for (int i = 0; i < session.getGraph()->size(); ++i) { // iterates on all vertices: {0,1,2,...}
        session.getGraph()->removeEdge(node, i); // sets all of u's row in edges vector to 0
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

void Virus::infectNode(Session& session) { // a Virus only infects its host
    Graph* g = session.getGraph();
    g->infectNode(this->nodeInd);
    session.enqueueInfected(this->nodeInd);
}

void Virus::occupy(Session& session, int node) {
    // handle session and graph
    session.getGraph()->occupyNode(node);
    session.addAgent(Virus(node)); // spread (clone self) to neighbor node
    session.activeVirusesUp();
}

int Virus::findNextVictim(Session& session) const { // make a copy to the next victim, and then look for another one
    Graph* g = session.getGraph();
    vector<int> neighbors = g->getNeighbors(this->nodeInd);
     int neighbors_size = neighbors.size();
    for (int i = 0; i < neighbors_size; ++i) {
        if (g->isVirusFree(neighbors[i])) return neighbors[i];
    }
    // If no next victim, do:
    g->occupyNode(this->nodeInd); // Change this node's state to 'Occupied' instead of 'Infected'
    return -1; // Return 'no next victim' signal
}

void Virus::act(Session &session) {
    /* action types (each occurs in a single iteration):
     * (1) Infect nodeInd and spread to first neighbor
     * (2) Spread to next neighbor
     * (3) Delete self */
    if (!this->is_active) return; // checks if the virus is active.
    if (session.getGraph()->isVirusFree(this->nodeInd)) occupy(session, this->nodeInd);
    if (!session.getGraph()->isInfected(this->nodeInd)) infectNode(session); // check if current node is infected
    // Continue to next victim:
    int next_victim = this->findNextVictim(session);
    if (next_victim == -1) this->deactivate(session);
    else this->occupy(session, next_victim);
}

void Virus::deactivate(Session& session) {
    this->is_active = false;
    session.activeVirusesDown();
}

int Virus::getNode() const {
    return this->nodeInd;
}

Virus* Virus::clone() const {
    return new Virus(*this);
}

Virus::Virus(const Virus &virus) : nodeInd(virus.getNode()) {/*Copy-Constructor*/}

ContactTracer* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

ContactTracer::ContactTracer(const ContactTracer &contactTracer) {/*Copy-Constructor*/}

Virus::~Virus() { /*delete virus object*/ }

ContactTracer::~ContactTracer() { /*delete ContactTracer object*/ }

char ContactTracer::getType() const {
    return 'C';
}
char Virus::getType() const {
    return 'V';
}
