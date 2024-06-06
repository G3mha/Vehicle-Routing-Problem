# Vehicle Routing Problem (VRP)

Author: Enricco Gemha

**Go to `main.ipynb` file to run this project**

## Approaches to the problem

### 1. Global Search

### 2. Nearest Neighbor

While it does not guarantee an optimal solution, it usually provides a good approximation in a much shorter runtime compared to evaluating all permutations. Some of its benefits are:

- **Efficiency**: It significantly reduces the computational complexity by avoiding the factorial growth associated with generating all permutations.

- **Simplicity**: The heuristic is straightforward to implement and understand.

- **Performance**: It often yields a reasonably good solution quickly, making it suitable for large problem instances where an exact solution is computationally infeasible.

### 3. OpenMP paralellization

To improve the performance using OpenMP, we can parallelize the for loops where independent iterations can be executed concurrently, specially on the following parts:

- **Generating Permutations**: This part is inherently sequential due to the nature of permutations generation, so it doesn't benefit from parallelization.

- **Valid Routes Calculation**: We can parallelize the outer loop that iterates over all routes to determine valid routes.

- **Finding the Best Route**: We can parallelize the outer loop that iterates over valid routes to find the one with the minimum cost.

This way, the performance can be improved when number of routes (permutations) is large.
