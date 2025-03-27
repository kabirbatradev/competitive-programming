// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using xyz = tuple<int, int, int>;
using xy = pair<int, int>;

set<xyz> visited;
set<xyz> visiting;

set<xy> visited2D;
set<xy> visiting2D;

struct Solution {
  Solution() {
  
    int k; cin >> k; // num of needles

    map<xyz, vector<xyz>> adjList;
    set<xyz> uniqueNodes;

    map<xy, vector<xy>> adjList2D;
    set<xy> uniqueNodes2D;

    for (int i = 0; i < k; i++) {
      // each one of these represents an edge between 2 nodes
      int x1, y1, z1;
      int x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      xyz xyz1 = {x1, y1, z1};
      xyz xyz2 = {x2, y2, z2};

      // populate adjList by showing connection between 2 coords
      adjList[xyz1].push_back(xyz2);
      adjList[xyz2].push_back(xyz1);

      // populate unique nodes 
      uniqueNodes.insert(xyz1);
      uniqueNodes.insert(xyz2);

      // 2d version:
      xy xy1 = {x1, y1};
      xy xy2 = {x2, y2};
      if (xy1 == xy2) continue; // do not insert self edges into adj list

      adjList2D[xy1].push_back(xy2);
      adjList2D[xy2].push_back(xy1);

      // populate unique nodes 
      uniqueNodes2D.insert(xy1);
      uniqueNodes2D.insert(xy2);
    }

    // run dfs on every node to look for cycles
    // {-1, -1, -1} is a dummy parent; works because all coords are in range [1, 1000)
    bool cycle = false;
    for (xyz node : uniqueNodes) {
      if (dfs(node, {-1, -1, -1}, adjList)) {
        cycle = true;
        break;
      }
    }
    cout << (cycle ? "True closed chains" : "No true closed chains") << '\n';

    // 2d version:
    cycle = false;
    for (xy node : uniqueNodes2D) {
      if (dfs2D(node, {-1, -1}, adjList2D)) {
        cycle = true;
        break;
      }
    }
    cout << (cycle ? "Floor closed chains" : "No floor closed chains") << '\n';
  }

  // visiting and visited are global variables 
  // true if there is a cycle
  bool dfs(xyz node, xyz parentNode, map<xyz, vector<xyz>>& adjList) {
    if (visiting.count(node)) return true;
    if (visited.count(node)) return false;

    // mark as visited and visiting
    visited.insert(node);
    visiting.insert(node);
    for (xyz neighbor : adjList[node]) {
      if (neighbor == parentNode) continue; // skip parent because otherwise we would find false cycle
      if (dfs(neighbor, node, adjList)) return true; // if cycle found, return true early
    }
    // no longer visiting
    visiting.erase(node);

    return false; // no cycle
  }

  // 2d version
  bool dfs2D(xy node, xy parentNode, map<xy, vector<xy>>& adjList2D) {
    if (visiting2D.count(node)) return true;
    if (visited2D.count(node)) return false;

    // mark as visited and visiting
    visited2D.insert(node);
    visiting2D.insert(node);
    for (xy neighbor : adjList2D[node]) {
      if (neighbor == parentNode) continue; // skip parent because otherwise we would find false cycle
      if (dfs2D(neighbor, node, adjList2D)) return true; // if cycle found, return true early
    }
    // no longer visiting
    visiting2D.erase(node);

    return false; // no cycle
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

/*
find if cycle exists (in shadow)

if two nodes have same shadow position, they cannot be both used because all shadows have to be distinct
therefore, two nodes with the same shadow can be treated as the same node

we actually need to find whether or not there are true cycles
and whether or not there are shadow cycles

every node is represented by xyz 
adjacency list:
  index: xyz
  output: list of nodes (xyz) that this node is connected to
  data structure: map from tuple of 3 ints --> vector of tuples

then redo this process but with pairs of xy 

how to find cycles: 
  run dfs every node (skip if already visited)
  keep track of visited (all false by default)
  for each dfs:
    keep track of whats in the current stack, which maybe we can call "visiting"
    then when we go to new nodes, if one is already visited, we skip it
    BUT if one is also already in "visiting", then we have a cycle
      we can just break because we are looking for cycles
    but yeah otherwise we can just call dfs on that node (maybe we have a recursive function we are working with)
    and we also mark visiting to true for that current node
    and visited is true ofc
    and then when we have finally gone in all directions possible
    we can mark visiting to false for the current node
    but leave visited to true

issue: since these graphs are undirected, we can go from node to neighbor and back
  and that would be considered a cycle
solution: make every node know its "parent", and skip that when considering neighbors

issue with 2d version: we could have the same edge twice
  this would cause the adj list to try to visit the same edge multiple times
  is this an issue? or should the code still work?
  i think the code still works because, in the second visit, the node would be marked as visited and skipped

actual issue with 2d version: self edges
  edge between nodes with only differing z values will now look like self edge
  code would try to visit itself and see that itself is already in the "visiting" set
solution:
  do not insert self edges into adj list
*/