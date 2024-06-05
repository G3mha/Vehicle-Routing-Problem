#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <sstream>

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
    vector<Edge> edges;
    map<int, int> demands;

    // Read and parse the input file
    read_vrp_input(input_filepath, num_nodes, demands, edges);

    num_nodes = demands.size() + 1;
    cout << "Number of edges: " << edges.size() << endl;
    cout << "Number of nodes: " << num_nodes << endl;

    vector<vector<int>> matrix(num_nodes);

    // Fill the spaces of the matrix with -1
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i].resize(matrix.size(), -1);
    }

    for (auto edge : edges) {
        int u = edge.from;
        int v = edge.to;
        int w = edge.weight;
        matrix[u][v] = w;
    }

    return 0;
}
