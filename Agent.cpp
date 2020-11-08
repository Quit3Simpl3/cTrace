#include "Agent.h"

/*Agent::Agent() : session () { // default constructor - is this REALLY necessary?

}*/

Agent::Agent(Session &session) : session(session) {
    this->session = session;
}

ContactTracer::ContactTracer(Session &session) : Agent(session) {
    // TODO
}

void ContactTracer::act() { // Contact Tracer act
    // TODO:
    // 1) Dequeue a node from infection queue
    // 2) create BFS by TreeType from node
    // 3) use treeTrace() to get the necessary node
    // 4) remove all the node's edges
}

Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {
    // TODO
}

void Virus::act() {
    // TODO
}
