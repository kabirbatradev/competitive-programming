// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  int n; // make n global
  Solution(int n) : n(n) {

    // intersections from 0 to n

    vector<pair<int, int>> positions(n);

    for (int i = 0; i < n; i++) {
      int x, y; cin >> x >> y;
      positions[i] = {x, y};
    }

    int m; cin >> m;
    // number of edges

    vector<vector<double>> adjMatrix(n, vector<double>(n, DBL_MAX)); 
    // DBL_MAX for no edge

    // populate adj matrix:
    for (int i = 0; i < m; i++) {
      int a, b; cin >> a >> b; // intersection numbers

      auto [x1, y1] = positions[a];
      auto [x2, y2] = positions[b];

      // sqrt of a^2 + b^2 
      double distance = sqrt(
        (x2 - x1) * (x2 - x1) + 
        (y2 - y1) * (y2 - y1)
      );

      adjMatrix[a][b] = distance;
      adjMatrix[b][a] = distance;

    }

    // run floyd warshalls to get runtime
    double noNewEdgeCost = floydWarshalls(adjMatrix);

    
    pair<int, int> bestEdge = {-1, -1}; // pair of intersections
    double bestTotalCost = noNewEdgeCost;
    
    // now go through all pairs, create a new edge if it doesnt already exist, and run a new iteration
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) { // start at i+1 so we dont do the same pair again
        if (adjMatrix[i][j] != DBL_MAX) continue; // skip if this edge already exists

        // reuse old code, create new edge between intersections i and j
        int a = i;
        int b = j;

        auto [x1, y1] = positions[a];
        auto [x2, y2] = positions[b];

        // sqrt of a^2 + b^2 
        double distance = sqrt(
          (x2 - x1) * (x2 - x1) + 
          (y2 - y1) * (y2 - y1)
        );

        adjMatrix[a][b] = distance;
        adjMatrix[b][a] = distance;

        // now run floyd warshalls again and do comparisons
        double cost = floydWarshalls(adjMatrix);
        if (cost < bestTotalCost) {
          bestEdge = {i, j};
          bestTotalCost = cost;
        }

        // now remove this edge 
        adjMatrix[a][b] = DBL_MAX;
        adjMatrix[b][a] = DBL_MAX;
      }
    }


    // if best edge is still -1, -1, no combination was better
    // otherwise we have data stored in bestEdge, bestTotalCost, and noNewEdgeCost

    /* expected output:
    adding 0 4 reduces 834.3724683377 to 537.3468586201
    adding 0 2 reduces 339.9989622408 to 315.4205424223
    no addition reduces 341.4213562373
    */

    if (bestEdge == make_pair(-1, -1)) {
      printf("no addition reduces %lf\n", noNewEdgeCost);
      // cout << "no addition reduces " << noNewEdgeCost << '\n';
    }
    else {
      printf("adding %d %d reduces %lf to %lf\n", bestEdge.first, bestEdge.second, noNewEdgeCost, bestTotalCost);
    }
  }

  // sum of all pairs shortest path:
  // not passing by value because we edit it directly
  double floydWarshalls(vector<vector<double>> adjMatrix) {

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (adjMatrix[i][k] == DBL_MAX || adjMatrix[k][j] == DBL_MAX) continue;
          adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
        }
      }
    }

    // sum up shortest path of all pairs:
    double total = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) { // start at i+1 so we don't double count pairs
        total += adjMatrix[i][j];
      }
    }

    return total;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  cout.precision(8); // # decimal places
  cout << fixed; // force precision decimal places

  // one solution object per test case:
  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    Solution s(n);
  }
}

/*
nodes: intersections
  x y coordinate pair
edges: 2 way roads between intersections
  start xy, end xy
  weight of edge = length

measure of total commute time: sum of shortest path between all pairs
  note Floyd Warshalls exists 

problem statement: 
  add one edge, reduce the commute time as much as possible
guaranteed: all intersections are already connected

brute force:
  go through every pair of intersections
  add an edge between them
  then run floyd warshalls to get all pairs shortest path
  store the best case (which pair of  intersections, and new shortest path)
*/