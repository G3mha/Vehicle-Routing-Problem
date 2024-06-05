#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <map>
#include <string>

struct Edge {
    int from;
    int to;
    int weight;
};

void read_vrp_input(const std::string& filename, int& num_nodes, std::map<int, int>& demands, std::vector<Edge>& edges);

#endif // UTILS_H
