/* For testing purposes only. */

#include "Graph.h"
#include "Session.h"
#include "Agent.h"
#include "Tree.h"
#include <iostream>
using namespace std;

class Tester {
public:
    Tester(const string &path) :
    session(path) {}

    void run_tests() {
//        this->test_copy();
        this->test_move();
    }

private:

    // Create new objects for all classes:
    Virus* virus = new Virus(42);
    ContactTracer contact_tracer = ContactTracer();
    CycleTree treeC = CycleTree(35, 2);
    MaxRankTree treeM = MaxRankTree(35);
    RootTree treeR = RootTree(35);
    vector<vector<int>> m = {{0,1,0}, {1,0,1}, {0,1,0}};
    Graph graph = Graph(m);
    Session session;

    void test_copy_ass() {
        cout << "COPY ASSIGNMENT TEST" << endl;
        // Virus:
//        Virus v = virus;
        // Contact Tracer:
        ContactTracer ct = contact_tracer;

        // CycleTree:


        // Session:
        Session s = session;

        // Graph:
        Graph g = graph;
    }

    void test_move_ass() {
        // TOOD
    }

    void test_delete() {
        // TOOD
    }

    /*void test_copy() {
        cout << "COPY CONSTRUCTOR TEST" << endl;

        // Virus:
//        Virus v = Virus(virus);
//        cout << "virus=" << &virus << endl;
//        cout << "v=" << &v << endl;
        // Contact Tracer:
        ContactTracer ct = ContactTracer(contact_tracer);
        cout << "contact_tracer=" << &contact_tracer << endl;
        cout << "ct=" << &ct << endl;
        // Cycle Tree:
        CycleTree tc = CycleTree(treeC);
        cout << "treeC=" << &treeC << endl;
        cout << "tc=" << &tc << endl;
        // MaxRank Tree:
        MaxRankTree tm = MaxRankTree(treeM);
        cout << "treeM=" << &treeM << endl;
        cout << "tm=" << &tm << endl;
        // Root Tree:
        RootTree tr = RootTree(treeR);
        cout << "treeR=" << &treeR << endl;
        cout << "tr=" << &tr << endl;
        // Session:
        Session s = Session(session);
        cout << "session=" << &session << endl;
        cout << "s=" << &s << endl;
        // Graph:
        Graph g = Graph(graph);
        cout << "graph=" << &graph << endl;
        cout << "g=" << &g << endl;

        if (
                &virus == &v ||
                &contact_tracer == &ct ||
                &treeC == &tc ||
                &treeM == &tm ||
                &treeR == &tr ||
                &session == &s ||
                &graph == &g
                ) {
            cout << "ONE OF THE ADDRESSES WASN'T CHANGED - COPY FAILD." << endl;
        }
        else {
            cout << "ALL ADDRESSES ARE DIFFERENT - COPY SUCCESSFUL." << endl;
        }
    }*/

    void test_move() {
        // Virus:
        Virus* v;
        cout << "virus=" << virus << endl;
        cout << "v=" << v << endl;
        // Contact Tracer:
        ContactTracer ct = ContactTracer(contact_tracer);
        cout << "contact_tracer=" << &contact_tracer << endl;
        cout << "ct=" << &ct << endl;
        // Cycle Tree:
        CycleTree tc = CycleTree(treeC);
        cout << "treeC=" << &treeC << endl;
        cout << "tc=" << &tc << endl;
        // MaxRank Tree:
        MaxRankTree tm = MaxRankTree(treeM);
        cout << "treeM=" << &treeM << endl;
        cout << "tm=" << &tm << endl;
        // Root Tree:
        RootTree tr = RootTree(treeR);
        cout << "treeR=" << &treeR << endl;
        cout << "tr=" << &tr << endl;
        // Session:
        Session s = Session(session);
        cout << "session=" << &session << endl;
        cout << "s=" << &s << endl;
        // Graph:
        Graph g = Graph(graph);
        cout << "graph=" << &graph << endl;
        cout << "g=" << &g << endl;

        if (
                &virus == &v &&
                &contact_tracer == &ct &&
                &treeC == &tc &&
                &treeM == &tm &&
                &treeR == &tr &&
                &session == &s &&
                &graph == &g
                ) {
            cout << "ALL ADDRESSES ARE THE SAME - MOVE SUCCESSFUL." << endl;
        }
        else {
            cout << "AT LEAST ONE OF THE ADDRESSES IS DIFFERENT - MOVE FAILED." << endl;
        }
    }
};