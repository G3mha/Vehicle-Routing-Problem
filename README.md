# Vehicle Routing Problem (VRP)

Author: Enricco Gemha

## How to run the project

*The commands below target the architecture of MacOS, which I use. Some tweaks might be necessary to run in other OSs.*

First, compile each file inside implementations.

```bash
g++ -std=c++11 -o global_search global_search.cpp utils.cpp
g++ -std=c++11 -o nearest_neighbor nearest_neighbor.cpp utils.cpp
clang++ -fopenmp -std=c++11 -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -o omp omp.cpp utils.cpp
```

Then, execute them.

```bash
./<executable_name> <input_filepath> <capacity>
```

## Approaches to the problem

### 1. Global Search

### 2. Nearest Neighbor

While it does not guarantee an optimal solution, it usually provides a good approximation in a much shorter runtime compared to evaluating all permutations.

I decided to choose it based on the following aspects:

- Efficiency: It significantly reduces the computational complexity by avoiding the factorial growth associated with generating all permutations.

- Simplicity: The heuristic is straightforward to implement and understand.

- Performance: It often yields a reasonably good solution quickly, making it suitable for large problem instances where an exact solution is computationally infeasible.

### 3. OpenMP paralellization
