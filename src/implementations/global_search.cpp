#include <algorithm>
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

    vector<vector<int>> routes;

    // Calculate the number of permutations of the nodes
    int permutations = 1;
    for (int i = 1; i < num_nodes; i++) {
        permutations *= i;
    }

    // Generate all permutations of the nodes (excluding the depot)
    vector<int> nodes;
    for (int i = 1; i < num_nodes; ++i) {
        nodes.push_back(i);
    }

    do {
        vector<int> route = {0};  // Start with the depot
        route.insert(route.end(), nodes.begin(), nodes.end());
        route.push_back(0);  // End with the depot
        routes.push_back(route);
    } while (next_permutation(nodes.begin(), nodes.end()));

    // Get all valid routes
    vector<vector<int>> valid_routes;
    for (const auto& path : routes) {
        vector<int> new_path;
        new_path.push_back(0);  // Start with depot (0)
        int total_capacity_used = 0;

        for (size_t j = 0; j < path.size() - 1; ++j) {
            int node = path[j];
            int next_node = path[j + 1];

            if (matrix[node][next_node] != -1 && total_capacity_used + demands[next_node] <= capacity) {
                new_path.push_back(next_node);
                total_capacity_used += demands[next_node];
            } else {
                if (new_path.back() != 0) {  // Prevent consecutive zeros
                    new_path.push_back(0);  // Return to depot to reset capacity
                }
                total_capacity_used = 0;  // Reset capacity after returning to depot

                if (matrix[0][next_node] != -1) {  // If there is a path from depot to next_node
                    new_path.push_back(next_node);
                    total_capacity_used += demands[next_node];
                }
            }
        }

        if (new_path.back() != 0) {  // Avoid appending 0 if already at depot
            new_path.push_back(0);
        }

        valid_routes.push_back(new_path);
    }

    // Get the best route
    int best_cost = INT_MAX;
    vector<int> best_route;
    for (const auto& route : valid_routes) {
        int cost = 0;
        for (size_t i = 0; i < route.size() - 1; ++i) {
            cost += matrix[route[i]][route[i + 1]];
        }

        if (cost < best_cost) {
            best_cost = cost;
            best_route = route;
        }
    }


    // Print the best route
    cout << "Best route: ";
    for (int node : best_route) {
        cout << node << " ";
    }
    cout << "\n";

    cout << "Cost: " << best_cost << endl;

    return 0;
}
