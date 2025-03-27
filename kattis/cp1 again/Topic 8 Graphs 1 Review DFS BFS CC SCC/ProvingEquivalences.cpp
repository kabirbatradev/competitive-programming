// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  map<int, vector<int>> adjList; 
  // vector<vector<int>> adjList; // could use a vector instead, because nodes are 0 to n-1
  // set<int> uniqueNodes; don't need unique nodes either for same reason

  // node --> discovery number
  map<int, int> discoveryNum;
  int nextDiscoveryNum = 0;

  // node --> the smallest reachable (from this node) discovery number 
  map<int, int> smallestReachable;

  // stack of nodes in current DFS/SCC
  stack<int> s;

  set<int> visited;
  set<int> visiting; // aka inside of stack

  vector<vector<int>> allSCCs;

  Solution() {

    int n; cin >> n; // number of statements (nodes)
    int m; cin >> m; // number of implications (edges)

    for (int i = 0; i < m; i++) {
      int x, y; cin >> x >> y;
      // input node is from 1 to n, so shift -1
      x--;
      y--;

      // populate adj list with edge x --> y showing s1 implies s2
      adjList[x].push_back(y);

    }


    // identify SCCs:
    // run dfs on every not visited node
    for (int node = 0; node < n; node++) {
      if (discoveryNum.count(node) != 0) continue; // node already explored

      dfs(node);
    }

    // SCCs are stored in vector<vector<int>> allSCCs

    // color the SCCs nodes: give each SCC a number, and label each node with its SCC number O(1) access
    // node --> sccNumber
    vector<int> nodeToSCCNum(n);
    int sccNumber = 0;
    for (vector<int>& scc : allSCCs) {
      for (int node : scc) {
        nodeToSCCNum[node] = sccNumber;
      }
      sccNumber++;
    }

    // special case: if there is only 1 or 0 SCCs, then we don't need any new edges
    if (sccNumber <= 1) {
      cout << 0 << '\n';
      return;
    }

    // go through every edge in adjList:
    // if edge connects 2 SCCs together, then add it to the adj list 
    // (note that there could be duplicates) 

    // keep track of which SCCs still have an in-degree of 0
    // keep track of which SCCs still have an out-degree of 0

    // assume all sccs have 0 indegree 
    unordered_set<int> sccsWith0InDegree;
    unordered_set<int> sccsWith0OutDegree;
    for (int i = 0; i < sccNumber; i++) {
      sccsWith0InDegree.insert(i);
      sccsWith0OutDegree.insert(i);
    }

    // look at edges between SCCs, and remove SCCs that now have an edge going towards them
    for (int node = 0; node < n; node++) {
      for (int neighbor : adjList[node]) {
        // check if neighbor and node are from two different SCCs
        if (nodeToSCCNum[node] != nodeToSCCNum[neighbor]) {
          // this is a new edge between SCCs
          // node --> neighbor
          // indegree of neighbor is guaranteed to not be 0 

          // erase this scc num if it now has an in-degree
          // the 'neighbor' now has +1 in-degree
          auto it = sccsWith0InDegree.find(nodeToSCCNum[neighbor]);
          if (it != sccsWith0InDegree.end()) {
            sccsWith0InDegree.erase(it);
          }

          // and out-degree case:
          // the 'node' now has +1 out-degree
          it = sccsWith0OutDegree.find(nodeToSCCNum[node]);
          if (it != sccsWith0OutDegree.end()) {
            sccsWith0OutDegree.erase(it);
          }
        }
        
      }
    }
    
    // # SCCs with in-degree 0 = # dominoes to knock over
    cout << max(sccsWith0OutDegree.size(), sccsWith0InDegree.size()) << '\n';
  }

  void dfs(int node) {
    discoveryNum[node] = nextDiscoveryNum++;
    smallestReachable[node] = discoveryNum[node]; // initial value is current node's discovery num itself

    // push current node onto stack, mark as visited and visiting
    s.push(node);
    visiting.insert(node);
    // visited.insert(node); replaced with existance of discoveryNum

    for (int neighbor : adjList[node]) {
      
      if (visiting.count(neighbor)) {
        // this neighbor is already in the stack, so we are basically reaching a node with a smaller discovery number
        smallestReachable[node] = min(smallestReachable[node], discoveryNum[neighbor]);
      }
      if (discoveryNum.count(neighbor)) continue; // skip if this node is already discovered

      // otherwise, dfs from this unvisited neighbor and use its smallest reachable
      dfs(neighbor);
      smallestReachable[node] = min(smallestReachable[node], smallestReachable[neighbor]);
      
    }

    // we have an SCC if smallest reachable is still discovery num of the current node
    // pop from stack to create new SCC
    // otherwise, leave nodes in stack 

    if (smallestReachable[node] == discoveryNum[node]) {
      vector<int> newSCC;
      while (true) {
        int top = s.top(); s.pop();
        visiting.erase(top); // dont forget to remove from visiting aka "in stack"
        
        newSCC.push_back(top); // all nodes in stack (up to current node) are in new SCC

        if (top == node) {
          break;
        }
      }

      allSCCs.push_back(newSCC); // add to list of all SCCs
    }

    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places

  // create new instance of solution for each test case
  int tc; cin >> tc;
  for (int t = 0; t < tc; t++) {
    Solution s;
  }
}


/*
given some directed edges between nodes (and total # nodes)
goal: get minimum number of new edges needed so that all nodes are in SCC

core idea:
  treat each SCC as a single node
  find edges between SCC (go through adj list)
  this creates a DAG of all of all of the SCCs!

finally: 
  compare the # of 0 in-degree and 0 out-degree nodes in the DAG
  # edges needed = max 

logic: tried a couple of examples
  if the DAG has a few leaves, then each leaf has to connect back up to the roots
  but if it has more roots, then we need one for each root too

edge case: if there is only 1 or 0 SCCs, then we should not add any new edges!
*/