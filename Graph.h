#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph{
public:
    Graph(){}; // Default constructor
    Graph(std::vector<std::vector<int>> matrix); // DO NOT CHANGE!
//    virtual ~Graph(){}; // Destructor
    Graph(const Graph *other); // Copy-Constructor

    void infectNode(int nodeInd); // DO NOT CHANGE!
    bool isInfected(int nodeInd); // DO NOT CHANGE!
    void occupyNode(int nodeInd);
    bool isVirusFree(int nodeInd);
    vector<int> getNeighbors(int node);
    int getInfectedCounter() const;
    int size() const;
    vector<int> getEdge(int k) const;
    void removeEdge(int u, int v);
    std::vector<std::vector<int>> getEdges();
    std::vector<int> getInfectedNodes();
    
private:
    std::vector<std::vector<int>> edges; // DO NOT CHANGE!
    std::vector<int> infections; // infection[i]=1 --> node i is infected
    std::vector<int> virus_free;
    std::vector<int> infected_nodes; // list of infected nodes by order of infection
    void _infectedCounterUp();
    void _infectedCounterDown();
    void _setInfectedCounter(int val);
    int _infected_counter;
};

#endif