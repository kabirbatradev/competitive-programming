// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
      
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
  node: answer choices aka activities
  directed edge: from activity to more prefered activity

graph question: identify SCCs
output format: 
  every line is an SCC
  output SCC in sorted order
  output all SCCs in sorted order (just compare their lexicographically smallest activity)
    note that all SCCs are disjoint
  
*/
