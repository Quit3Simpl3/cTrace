# cTrace
##### System Programming course assignment. Received perfect score (100/100).
#### Simulates the elimination of a plague by tracing the contacts of infected graph nodes and quarantining them (by cutting-off their edges to other nodes in the graph).
#### The user chooses a number of contact tracers and viruses, and the starting nodes in the graph for the viruses.

#### INPUT:
##### The input should be a JSON file containing:
- The adjacency-matrix ([Wikipedia](https://en.wikipedia.org/wiki/Adjacency_matrix)) for the graph, as an array of int arrays.
- The agents to use in the simulation (agent = Virus/Contact Tracer), with the starting node for the viruses, as an array of ```["V", 3]``` for creating a virus in node 3, ```["C", -1]``` for creating a contact tracer.
- The method of contact tracing to use: 'M' for MaxRankTree, 'C' for CycleTree, 'R' for RootTree. // TODO: Add explanations for the tree types.
##### Input JSON file is available in the Example folder.

#### USAGE:
##### 1. Compile:
```
$ make
```
##### 2. Run:
```
$ cTrace "input.json"
```

#### OUTPUT:
##### A JSON file named output.json containing the new, modified graph and a list of the infected nodes.
