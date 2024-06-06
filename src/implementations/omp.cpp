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

    int num_nodes;            // Number of nodes
    vector<Edge> edges;       // Edges of the graph
    map<int, int> demands;    // Demands of the nodes

    // Read and parse the input file
    read_vrp_input(input_filepath, num_nodes, demands, edges);

    num_nodes = demands.size() + 1;         // Number of nodes (including the depot)
    vector<vector<int>> matrix(num_nodes);  // Adjacency matrix

    // Fill the spaces of the matrix with -1
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i].resize(matrix.size(), -1);
    }

    // Change the elements of the matrix with the captured weights of the edges
    for (auto edge : edges) {
        int u = edge.from;
        int v = edge.to;
        int w = edge.weight;
        matrix[u][v] = w;
    }

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

    // Get all routes between those permutations
    vector<vector<int>> routes;
    do {
        vector<int> route = {0};  // Start with the depot
        route.insert(route.end(), nodes.begin(), nodes.end());  // Add the nodes
        route.push_back(0);       // End with the depot
        routes.push_back(route);  // Store the route
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

            // Check if there is a path from node to next_node and if the capacity is not exceeded
            if (matrix[node][next_node] != -1 && total_capacity_used + demands[next_node] <= capacity) {
                new_path.push_back(next_node);              // Add next_node
                total_capacity_used += demands[next_node];  // Update capacity
            
            // If the capacity is exceeded, return to depot
            } else {
                if (new_path.back() != 0) {  // Prevent consecutive zeros
                    new_path.push_back(0);   // Return to depot to reset capacity
                }
                total_capacity_used = 0;  // Reset capacity after returning to depot

                if (matrix[0][next_node] != -1) {  // If there is a path from depot to next_node
                    new_path.push_back(next_node);              // Add next_node
                    total_capacity_used += demands[next_node];  // Update capacity
                }
            }
        }

        if (new_path.back() != 0) {  // Avoid appending 0 if already at depot
            new_path.push_back(0);   // Return to depot
        }

        valid_routes.push_back(new_path);  // Store the valid route
    }

    // Get the best route
    int best_cost = INT_MAX;  // INT_MAX is the maximum value for an int
    vector<int> best_route;
    for (const auto& route : valid_routes) {
        int cost = 0;
        for (size_t i = 0; i < route.size() - 1; ++i) {  // Iterate over the route
            cost += matrix[route[i]][route[i + 1]];      // Calculate the cost of the route
        }

        // Update the best route
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
