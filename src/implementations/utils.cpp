#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

void read_vrp_input(const std::string& filename, int& num_nodes, std::map<int, int>& demands, std::vector<Edge>& edges) {
    std::ifstream infile(filename);
    std::string line;

    if (!infile.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    // Read the number of nodes
    std::getline(infile, line);
    std::istringstream iss_num_nodes(line);
    iss_num_nodes >> num_nodes;

    // Read the demands
    for (int i = 0; i < num_nodes - 1; ++i) {
        std::getline(infile, line);
        std::istringstream iss(line);
        int node, demand;
        iss >> node >> demand;
        demands[node] = demand;
    }

    // Read the number of edges
    std::getline(infile, line);
    int num_edges;
    std::istringstream iss_num_edges(line);
    iss_num_edges >> num_edges;

    // Read the edges
    for (int i = 0; i < num_edges; ++i) {
        std::getline(infile, line);
        std::istringstream iss(line);
        int from, to, weight;
        iss >> from >> to >> weight;
        edges.push_back({from, to, weight});
    }

    infile.close();
}
