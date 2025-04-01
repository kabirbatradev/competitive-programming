// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int n, m; cin >> n >> m;

    vector<vector<int>> adjList(n);

    vector<int> inDegree(n, 0);

    // go through input
    for (int i = 0; i < m; i++) {
      int a, b; cin >> a >> b;
      // a is on top of b
      // a --> b

      // shift 1 through n to 0 through n-1 (I want to 0-index)
      a--;
      b--;

      // populate adj list
      adjList[a].push_back(b);

      // count in-degree of every node
      inDegree[b]++;
    }
    
    queue<int> q;

    for (int i = 0; i < n; i++) {
      if (inDegree[i] == 0) {
        q.push(i);
      }
    }

    vector<int> ans;

    // topological sort using queue of nodes with in-degree 0
    while (!q.empty()) {
      int node = q.front(); q.pop();

      // populate answer array by adding latest node in sorted order
      ans.push_back(node);

      for (int neighbor : adjList[node]) {
        inDegree[neighbor]--;
        if (inDegree[neighbor] == 0) {
          q.push(neighbor);
        }
      }
    }

    // if any node has in-degree not 0, then that node was not able to be 
    // put in the topological sort list, so the sort was impossible
    for (int i = 0; i < n; i++) {
      if (inDegree[i] != 0) {
        cout << "IMPOSSIBLE" << endl;
        return;
      }
    }

    for (int node : ans) {
      cout << (node+1) << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  Solution s;
}