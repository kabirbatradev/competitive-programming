// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
// using ll = long long;
#define int long long // replace all "int" with "long long"
using namespace std;

struct Solution {
  Solution() {
    int n, m, p; cin >> n >> m >> p;
    // n: number of buildings
    // m: # possible connections
    // p: num insecure buildings

    // buildings are 1 indexed (numbered), so we should -1

    // identify insecure buildings
    vector<bool> isInsecure(n, false);
    vector<int> insecureVector(p);
    for (int i = 0; i < p; i++) {
      int insecureNum; cin >> insecureNum;
      insecureNum--;

      // insecure.insert(insecureNum);
      isInsecure[insecureNum] = true;
      insecureVector[i] = insecureNum;
    }

    // read in potential edges and put into an adj list
    vector<vector<pair<int, int>>> adjList(n);
    int lSum = 0;
    for (int i = 0; i < m; i++) {
      int x, y, l; cin >> x >> y >> l;
      x--;
      y--;
      // x and y are buildings, l is the weight
      // no duplicate paths

      adjList[x].push_back({y, l}); // pair where second value is the weight
      adjList[y].push_back({x, l});

      lSum += l;
    }

    // edge case: no secure buildings:
    if (p == n) {
      // need to use every edge to make fully connected component
      // that would be n * (n-1) / 2 edges
      if (m == (n * (n-1) / 2)) {
        cout << lSum << '\n';
      }
      else {
        cout << "impossible" << '\n';
      }
      return;
    }

    // run mst algorithm: Prim's:

    // find a secure building to start with:
    int start = -1;
    for (int i = 0; i < n; i++) {
      if (!isInsecure[i]) {
        start = i;
        break;
      }
    }

    // now use a pq to pick edges to create MST
    // values are: weight, building #
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // max heap by default
    pq.push({0, start});
    
    int totalMSTWeight = 0;
    vector<bool> visited(n, false);
    int nodesAddedCounter = 0;

    while (!pq.empty()) {
      auto [weight, node] = pq.top(); pq.pop();

      if (visited[node]) continue; // double check visited, as we might have added the same node multiple times
      visited[node] = true;
      totalMSTWeight += weight;
      nodesAddedCounter++;

      for (auto [neighbor, weight] : adjList[node]) {
        // must be secure and not alr visited
        if (!isInsecure[neighbor] && !visited[neighbor]) {
          pq.push({weight, neighbor});
        }
      }
    }

    // a full MST would have (n-p) - 1 edges connecting all of the secure buildings
    // (n-p) nodes
    // if not, we dont have a complete MST, so its impossible
    if (nodesAddedCounter != (n-p)) {
      cout << "impossible" << '\n';
      return;
    }

    // now, every insecure building needs to be connected to the secure MST somewhere
    // and if that edge exists, they will be connected with everyone!
    // so find the best edge for each insecure
    // note: if an edge does not exist to connect the insecure building to the MST, we have an impossible case
    for (int insecure : insecureVector) {
      // find the minimum weight edge that connects this building to a secure building
      int minEdge = INT_MAX;
      for (auto [neighbor, weight] : adjList[insecure]) {
        // if secure building and new best weight
        if (!isInsecure[neighbor] && weight < minEdge) {
          minEdge = weight;
        }
      }

      // failed to find edge:
      if (minEdge == INT_MAX) {
        cout << "impossible" << '\n';
        return;
      }

      // add edge to total
      totalMSTWeight += minEdge;
    }

    // all insecure buildings have been successfully connected
    cout << totalMSTWeight << '\n';
  }
};



// using "signed" works around "int" being replaced with long long
signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit); // idk what this does but it prevents me from doing while (cin >> n)
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  Solution s;
}

/*
this problem is an MST problem
need to connect all cities so that we can send a phone call from any building to any building
but some buildings are "insecure", which means they should not be used in the path between 2 cities

intuitive solution:
create an MST out of all "secure" buildings
greedily attach the insecure buildings to the main network
  if no edge to main network exists, its impossible
use prims algo:
  start at some secure building node
  use pq to consider new edges to add new buildings
  skip if alr visited or if not secure

edge case: all buildings are insecure:
  solution: would need edges between all buildings 
  note that it might be impossible (if not all edges exist)

edge case: we end up with multiple MSTs
  this means there are multiple disconnected secure networks
  this is an impossible case
  catch this by trying to build an MST and see if all nodes showed up by the end
*/