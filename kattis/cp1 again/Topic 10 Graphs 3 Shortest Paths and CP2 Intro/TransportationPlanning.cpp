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
    // set diagonal to 0s
    for (int i = 0; i < n; i++) {
      adjMatrix[i][i] = 0;
    }

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
    // turns adjMatrix into distance matrix

    
    pair<int, int> bestEdge = {-1, -1}; // pair of intersections
    double bestTotalCost = noNewEdgeCost;

    // now for all pairs, create a new edge if it doesnt already exist
    // then for every start and end, consider using that edge to see if the shortest path got better
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) { // start at i+1 so we dont do the same pair again

        // save old values
        double oldDistance = adjMatrix[i][j];

        // add the edge
        // reuse old code, create new edge between intersections/nodes i and j
        int a = i;
        int b = j;
        auto [x1, y1] = positions[a];
        auto [x2, y2] = positions[b];
        double distance = sqrt(
          (x2 - x1) * (x2 - x1) + 
          (y2 - y1) * (y2 - y1)
        );
        // only write the value if this edge is better than the shortest path already there:
        if (adjMatrix[a][b] <= distance) continue; // skip if this new edge is not better (prob bc edge alr exists)
        // adjMatrix[a][b] = distance;
        // adjMatrix[b][a] = distance;

        // accumulate improvement made by this edge existing:
        double totalSaved = 0;
        // for every start end:
        for (int start = 0; start < n; start++) {
          for (int end = start+1; end < n; end++) { // start at a+1, dont want to double count pairs

            // consider using this edge:
            // instead of a --> b
            // we want to do a --> i --> j --> b
            // adjMatrix[i][j] is our new edge
            // if (adjMatrix[a][i] == DBL_MAX || adjMatrix[j][b] == DBL_MAX) continue; // should never happen because completely connected
            
            // note: make sure diagonal is 0: otherwise we would not catch the case where this edge is the entire path
            double newCost = adjMatrix[start][i] + distance + adjMatrix[j][end];
            // we can also use the edge backward!
            // a --> j --> i --> b
            double newCost2 = adjMatrix[start][j] + distance + adjMatrix[i][end];

            newCost = min(newCost, newCost2);

            if (newCost < adjMatrix[start][end]) {
              totalSaved += adjMatrix[start][end] - newCost;
            }

          }
        }

        // update variables keeping track of best edge etc, use totalSaved
        double cost = noNewEdgeCost - totalSaved;
        if (cost < bestTotalCost) {
          bestEdge = {i, j};
          bestTotalCost = cost;
        }

        // now revert this edge 
        // adjMatrix[a][b] = oldDistance;
        // adjMatrix[b][a] = oldDistance;

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
  // nvm i want to pass by value
  double floydWarshalls(vector<vector<double>>& adjMatrix) {

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
  this is V^5 so it TLE

new idea: 
  modify floyd warshalls somehow...
  for every possible new edge:
    for every start and end node, consider using that new edge
    accumulate the total distance saved
*/