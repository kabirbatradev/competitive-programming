// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
#define int long long // replace all "int" with "long long"
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int n, m;
  Solution() {
    cin >> n >> m;

    // adj list with pairs of weight, connected city
    vector<vector<pair<int,int>>> adjList(n); // max n is 10e7 (million)
    for (int i = 0; i < m; i++) {
      int a, b, len;
      cin >> a >> b >> len;
      adjList[a].push_back({len, b});
      adjList[b].push_back({len, a});
    }

    // run DFS once to check if graph is fully connected
    // and get a "high" bound
    vector<bool> visited(n, false);
    int maxWeightUsed = dfs(0, INF, visited, adjList);
    // if not all nodes are visited, then impossible
    for (bool v : visited) {
      if (!v) {
        cout << "IMPOSSIBLE\n";
        return;
      }
    }

    // BSTA
    int low = 0;
    int high = maxWeightUsed;
    int best = maxWeightUsed; // min "max weight used" that allows for fully connected graph
    while (low <= high) {
      int mid = low + (high - low) / 2;

      visited.assign(n, false);
      maxWeightUsed = dfs(0, mid, visited, adjList);

      bool success = true;
      for (bool v : visited) {
        if (!v) {
          success = false;
          break;
        }
      }

      // try smaller max weight allowed
      if (success) {
        high = maxWeightUsed - 1;
        best = min(best, maxWeightUsed);
      }
      // failed, try larger max weight allowed
      else {
        low = mid + 1;
      }

    }

    cout << best << '\n';
  }

  // input: max edge weight allowed
  // output: max edge weight used
  int dfs(int node, int maxAllowedWeight, vector<bool>& visited, vector<vector<pair<int,int>>>& adjList) {
    if (visited[node]) return 0;
    visited[node] = true;

    int maxWeightUsed = 0;
    for (auto [weight, neighbor] : adjList[node]) {
      if (weight > maxAllowedWeight) continue;

      maxWeightUsed = max(maxWeightUsed, weight); // weight just used

      int w = dfs(neighbor, maxAllowedWeight, visited, adjList);
      maxWeightUsed = max(maxWeightUsed, w); // weights used in DFS

    }

    return maxWeightUsed;
  }
};

// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit); // idk what this does but it prevents me from doing while (cin >> n)
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
goal: connect all the cities such that the distance between any 2 pair of cities is minimized 
given set of edges

output minimum max distance between 2 cities
impossible if not all cities are connected

idea 1: BSTA: given a max edge weight, can we connect all the cities? can function is simply DFS
  runtime: log(10^9) * (V+E)

idea 2: MST: will use the smallest edges until all cities are connected
  use Kruskals algo to go through edges in sorted order
  the weight of the last edge used is the answer! 
  runtime: E log E 

about the same runtime?
*/