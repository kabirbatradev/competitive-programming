// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  map<int, vector<int>> adjList; 
  set<int> uniqueNodes;

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

  Solution(int n) {
    // n is # questions on the test

    for (int i = 0; i < n; i++) {
      // read in the question (5 answers, one selected answer)
      vector<int> potentialAnswers(5);
      for (int j = 0; j < 5; j++) {
        char c;
        cin >> c;
        potentialAnswers[j] = c - 'A'; // shift to integer from 0 to 25
      }

      char selectedAnswer;
      char c;
      cin >> c;
      selectedAnswer = c - 'A';

      // convert this to nodes and edges and populate adj list
      // nodes: potential answers
      // directed edges: less prefered answer --> selected answer
      // note: not all characters will show up as potential answers

      for (int p : potentialAnswers) {
        uniqueNodes.insert(p); // update unique nodes with new potential answers

        if (p == selectedAnswer) continue; // do not create edge if this was the answer selected

        // create edge: p --> selectedAnswer
        adjList[p].push_back(selectedAnswer);
      }

    }

    


    // identify SCCs:
    // run dfs on every not visited node
    for (int node : uniqueNodes) {
      if (discoveryNum.count(node) != 0) continue; // node already explored

      dfs(node);
    }
    

    // SCCs are stored in vector<vector<int>>
    // sort each individiual vector<int> first
    // then sort vector of vectors
    // then print all SCCs

    for (vector<int>& scc : allSCCs) {
      sort(scc.begin(), scc.end());
    }
    sort(allSCCs.begin(), allSCCs.end());

    // print:
    for (vector<int>& scc : allSCCs) {
      for (int node : scc) {
        cout << (char)(node + 'A') << " ";
      }
      cout << '\n';
    }
    
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
  string prefix = "";
  while (true) {
    int n; 
    cin >> n;
    if (n == 0) break;

    cout << prefix; // new line after every test case except last
    prefix = "\n";

    Solution s(n);
  }
}

/*
problem statement:
list of questions
each question has list of 5 answer choices
the user picks the one they prefer 

goal: 
  partition answer choices aka activities into sets
  for each set, if u grab any 2 nodes, they are contradictory (there is a cycle which includes them)
  make the minimum number of sets possible

how to represent as a graph:
  node: answer choices aka activities (integer from 0 to 25)
  directed edge: from activity to more prefered activity

graph question: identify SCCs
output format: 
  every line is an SCC
  output SCC in sorted order
  output all SCCs in sorted order (just compare their lexicographically smallest activity)
    note that all SCCs are disjoint


how to identify SCC: (tarjan's)
  for every node
    give a discovery number (skip this node if it alr has discovery number)
    identify the smallest discovery number that this node can reach
      by default, this should be itself
  as you dfs:
    update current node's "smallest reachable discovery number" with smallestReach of neighbor after dfs(neighbor)
      only update if its better
    if neighbor is in the current dfs stack, then we have a cycle, so update smallestReachable with 
      the discovery number of the neighbor (if its better)
    also add current node to a stack, and add to "visiting" for O(1) check if its in the stack 
    no need for global visited bc we have discovery number
  while backtracking:
    if node's smallestReachable is itself, then it is the "root of an scc",
    so pop from the stack until this node is reached (inclusive), 
    and everything that was in the stack is part of our SCC
  


*/
