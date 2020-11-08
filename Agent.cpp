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

    this->start_node = this->dequeueInfected(session); // get new infected node from queue
    Tree* tree = Tree::createTree(session, this->start_node); // this tree does nothing
    Tree* bfs_tree = tree->BFS(session, this->start_node); // maybe change BFS to 'static'?
    int patient = bfs_tree->traceTree();
    this->removeEdges(patient);
}

void ContactTracer::removeEdges(int node) {
    // TODO: remove node's edges
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {
    // TODO
}

void Virus::act(Session &session) {
    // TODO
}
