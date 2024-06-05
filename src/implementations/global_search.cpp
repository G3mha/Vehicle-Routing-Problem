#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "utils.h"
using namespace std;

int main(int argc, char* argv[]) {

    // Check if the number of arguments is correct
    if (argc != 3) {
        cout << "Incorrect arguments" << endl;
        cout << "Usage: ./<executable_name> <input_filepath> <capacity>" << endl;
        return 1;
    }

    string input_filepath = argv[1];  // Get the input file path
    int capacity = atoi(argv[2]);     // Get the capacity of the vehicle

    int num_nodes;
    std::map<int, int> demands;
    std::vector<Edge> edges;

    // Read and parse the input file
    read_vrp_input(input_filepath, num_nodes, demands, edges);

    // Print the parsed data
    std::cout << "Number of nodes: " << num_nodes << std::endl;
    std::cout << "Demands:" << std::endl;
    for (const auto& demand : demands) {
        std::cout << "Node " << demand.first << ": " << demand.second << std::endl;
    }
    std::cout << "Edges:" << std::endl;
    for (const auto& edge : edges) {
        std::cout << "From " << edge.from << " to " << edge.to << " with weight " << edge.weight << std::endl;
    }

    return 0;
}
