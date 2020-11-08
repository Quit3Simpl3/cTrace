#ifndef AGENT_H_
#define AGENT_H_

#include "Session.h"

#include <vector>

class Agent{
public:
    Agent(); // DO NOT CHANGE!

    virtual void act(Session& session)=0; // DO NOT CHANGE!
};

class ContactTracer: public Agent{
public:
    ContactTracer(); // DO NOT CHANGE!

    virtual void act(Session& session); // DO NOT CHANGE!
    void removeEdges(Session& session, int node);
    int dequeueInfected(Session& session);
private:
};


class Virus: public Agent{
public:
    Virus(int nodeInd); // DO NOT CHANGE!

    virtual void act(Session& session); // DO NOT CHANGE!
    void infectNode(Session& session, int node);
    int findNextVictim(Session& session);

private:
    const int nodeInd; // DO NOT CHANGE!
};

#endif

/*

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    
    virtual void act();
private:
    int dequeueInfected();
    int traceTree();
    int getNode();
    int start_node;
};
*/