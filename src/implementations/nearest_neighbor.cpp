#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <sstream>
#include <climits>
#include <unordered_set>
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

    // Nearest Neighbor Heuristic to find an approximate solution
    vector<int> best_route;
    int best_cost = INT_MAX;

    for (int start_node = 1; start_node < num_nodes; ++start_node) {
        vector<int> route = {0};  // Start with the depot
        unordered_set<int> visited = {0};  // Mark depot as visited
        int total_capacity_used = 0;
        int total_cost = 0;
        int current_node = 0;

        while (visited.size() < num_nodes) {
            int nearest_node = -1;
            int nearest_distance = INT_MAX;

            for (int next_node = 1; next_node < num_nodes; ++next_node) {
                if (visited.count(next_node) == 0 && matrix[current_node][next_node] != -1 &&
                    total_capacity_used + demands[next_node] <= capacity &&
                    matrix[current_node][next_node] < nearest_distance) {
                    nearest_node = next_node;
                    nearest_distance = matrix[current_node][next_node];
                }
            }

            if (nearest_node == -1) {
                // If no valid nearest node found, return to depot to reset capacity
                total_cost += matrix[current_node][0];
                route.push_back(0);
                total_capacity_used = 0;
                current_node = 0;
            } else {
                // Move to the nearest node
                total_cost += nearest_distance;
                total_capacity_used += demands[nearest_node];
                route.push_back(nearest_node);
                visited.insert(nearest_node);
                current_node = nearest_node;
            }
        }

        // Return to depot
        total_cost += matrix[current_node][0];
        route.push_back(0);

        if (total_cost < best_cost) {
            best_cost = total_cost;
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
