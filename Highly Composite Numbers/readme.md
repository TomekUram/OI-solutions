## Highly Composite Numbers Problem Statement:
Given a large natural number $N$, find the smallest integer $M \le N$ that has the maximum possible number of divisors. In other words, find the smallest Highly Composite Number within the range $[1, N]$.

## Solution $O(K \cdot \Pi(N))$ $K \approx 15$:
The solution explores the space of candidate numbers using a depth-first search (DFS) based on prime factorization. Instead of checking every integer, it constructs numbers by multiplying consecutive primes ($2, 3, 5, \dots$), ensuring the search space remains manageable.
