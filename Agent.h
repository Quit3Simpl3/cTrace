#ifndef AGENT_H_
#define AGENT_H_

#include "Session.h"

#include <vector>

class Agent{
public:
    Agent(); // DO NOT CHANGE!
//    virtual Agent* clone() const;
    virtual void act(Session& session)=0; // DO NOT CHANGE!
    virtual Agent* clone() const=0;
//    virtual Agent(const Agent &agent); // Copy-Constructor
    virtual ~Agent();
    virtual char getType()=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer(); // DO NOT CHANGE!
    ContactTracer(const ContactTracer &contactTracer); // Copy-Constructor
    ContactTracer *clone() const;
    virtual ~ContactTracer();

    char getType();

    virtual void act(Session& session); // DO NOT CHANGE!
    void removeAllEdges(Session& session, int node);
    int dequeueInfected(Session& session);
private:
};


class Virus: public Agent{
public:
    Virus(int nodeInd); // DO NOT CHANGE!
    Virus(const Virus &virus); // Copy-Constructor
    virtual ~Virus();

    char getType();

    virtual Virus* clone() const; // for copying

    virtual void act(Session& session); // DO NOT CHANGE!
    void infectNode(Session& session);
    void deactivate(Session& session);
    int getNode() const;

private:
    const int nodeInd; // DO NOT CHANGE!
    bool is_active=true; // Whether Virus.act() should run
    int findNextVictim(Session& session);
    void occupy(Session& session, int node);
};

#endif