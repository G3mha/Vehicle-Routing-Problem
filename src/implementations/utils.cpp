#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

void read_vrp_input(const std::string& filename, int& num_nodes, std::map<int, int>& demands, std::vector<Edge>& edges) {
    std::ifstream infile(filename);  // Open the file
    std::string line;                // Line to read the file

    // Check if the file is alreadyopen
    if (!infile.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    // Read the number of nodes (first line of the file)
    std::getline(infile, line);             // Read the first line
    std::istringstream iss_num_nodes(line); // Convert the line to a stream
    iss_num_nodes >> num_nodes;             // Read the number of nodes

    // Read the demands
    for (int i = 0; i < num_nodes - 1; ++i) {
        std::getline(infile, line);   // Read the line
        std::istringstream iss(line); // Convert the line to a stream
        int node, demand;             // Variables to store the node and demand
        iss >> node >> demand;        // Read the node and demand
        demands[node] = demand;       // Store the demand
    }

    // Read the number of edges
    std::getline(infile, line);              // Read the line
    int num_edges;                           // Variable to store the number of edges
    std::istringstream iss_num_edges(line);  // Convert the line to a stream
    iss_num_edges >> num_edges;              // Read the number of edges

    // Read the edges of the graph
    for (int i = 0; i < num_edges; ++i) {
        std::getline(infile, line);           // Read the line
        std::istringstream iss(line);         // Convert the line to a stream
        int from, to, weight;                 // Variables to store the from, to, and weight
        iss >> from >> to >> weight;          // Read the from, to, and weight
        edges.push_back({from, to, weight});  // Store the edge
    }

    infile.close();  // Close the file
}
