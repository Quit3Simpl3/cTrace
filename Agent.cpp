#include "Agent.h"
#include "Tree.h"

Agent::Agent() {
    // TODO
}

ContactTracer::ContactTracer() {
    // TODO
}

int ContactTracer::dequeueInfected(Session& session) {
    return session.dequeueInfected();
}

void ContactTracer::act(Session& session) {
    // 1) Dequeue a node from infection queue
    // 2) create BFS by TreeType from node
    // 3) use treeTrace() to get the necessary node
    // 4) remove all the node's edges
    int start_node = this->dequeueInfected(session); // get new infected node from queue
    Tree* bfs_tree = Tree::BFS(session, start_node);
    int patient = bfs_tree->traceTree();
    this->removeEdges(session, patient); // remove all the patient's edges
}

void ContactTracer::removeEdges(Session& session, int node) {
    Graph g = session.getGraph(); // TODO: change to reference?
    for (int i = 0; i < g.size(); ++i) { // iterates on all vertices: {0,1,2,...}
        g.removeEdge(node, i); // sets all of u's row in edges vector to 0
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {
    // TODO
}

void infectNode(Session& session, int node) {
    Graph g = session.getGraph();
    g.infectNode(node);
    session.enqueueInfected(node);
}

int Virus::findNextVictim(Session& session) { // make sure to only make a copy to the next victim, and then look for another one
    Graph g = session.getGraph();
    vector<int> neighbors = g.getNeighbors(this->nodeInd);
    for (int neighbor : neighbors) {
        if (g.isVirusFree(neighbor)) return neighbor;
    }
    return -1;
}

void Virus::act(Session &session) {
    // 1) infect this->nodeInd
    // 2) if this->nodeInd is infected, then: find next victim and spread to it
    // 3)
}
