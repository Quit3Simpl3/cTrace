#include "Session.h"
#include "json.hpp"
#include "Graph.h"
#include <fstream>

using namespace std;
using namespace nlohmann;

Session::Session(const std::string &path) {
    fstream stream(path);
    json j;
    stream >> j;
    vector<vector<int>> matrix = j.at("graph"); // creates adjacency matrix from config JSON
}
