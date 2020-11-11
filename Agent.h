#ifndef AGENT_H_
#define AGENT_H_

#include "Session.h"

#include <vector>

class Agent{
public:
    Agent(); // DO NOT CHANGE!
    virtual Agent* clone() const;
    virtual void act(Session& session)=0; // DO NOT CHANGE!
    virtual ~Agent(){};
};

class ContactTracer: public Agent{
public:
    ContactTracer(); // DO NOT CHANGE!
    virtual ~ContactTracer(){}; // Destructor
    Agent *clone() const;

    virtual void act(Session& session); // DO NOT CHANGE!
    void removeAllEdges(Session& session, int node);
    int dequeueInfected(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd); // DO NOT CHANGE!
//    Virus(const Virus &virus); // Copy Constructor
    virtual ~Virus(){}; // Destructor
    Agent *clone() const;

    virtual void act(Session& session); // DO NOT CHANGE!
    void infectNode(Session& session);
    void deactivate(Session& session); // set Virus as not active
    int getNode() const; // return nodeInd

private:
    const int nodeInd; // DO NOT CHANGE!
    bool is_active=true; // Whether Virus.act() should run
    int findNextVictim(Session& session); // get next node to spread to
    void occupy(Session& session, int node); // spread to node
};

#endif