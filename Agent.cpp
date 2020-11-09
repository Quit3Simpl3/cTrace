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
    if (start_node == -1) return; // dequeueInfected returns -1 if empty
    Tree* bfs_tree = Tree::BFS(session, start_node);
    int patient = bfs_tree->traceTree();
    this->removeEdges(session, patient); // remove all the patient's edges
}

void ContactTracer::removeEdges(Session& session, int node) {
    for (int i = 0; i < session.getGraph().size(); ++i) { // iterates on all vertices: {0,1,2,...}
        session.getGraph().removeEdge(node, i); // sets all of u's row in edges vector to 0
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {
    // TODO
}

void Virus::infectNode(Session& session) {
    this->infectNode(session, this->nodeInd);
}

void Virus::infectNode(Session& session, int node) {
    // handle session and graph
    Graph g = session.getGraph();
    g.infectNode(node);
    session.enqueueInfected(node);
    // copy virus if node is neighbor
    if (node != this->nodeInd) {
        const Agent* virus = new Virus(node); // spread to the next victim
        session.addAgent(*virus);
    }
}

int Virus::findNextVictim(Session& session) { // make a copy to the next victim, and then look for another one
    Graph g = session.getGraph();
    vector<int> neighbors = g.getNeighbors(this->nodeInd);
    for (int neighbor : neighbors) {
        if (g.isVirusFree(neighbor)) return neighbor;
    }
    g.occupyNode(this->nodeInd);
    // TODO: delete this virus
    return -1;
}

void Virus::act(Session &session) {
    // 1) infect this->nodeInd
    // 2) if this->nodeInd is infected, then: find next victim and copy self to it

    if (!this->is_active) return; // checks if the virus is active.
    if (!session.getGraph().isInfected(this->nodeInd)) infectNode(session); // check if current node is infected
    else { // infect neighbor
        int next_victim = this->findNextVictim(session);
        if (next_victim == -1) delete this; // TODO: remove this from agent list in session
        else this->infectNode(session, next_victim);
    }
}
