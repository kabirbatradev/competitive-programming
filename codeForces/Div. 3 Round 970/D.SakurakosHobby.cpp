#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int t; cin >> t;
  for (int tc = 0; tc < t; tc++) {
    int n; cin >> n;
    vector<int> permutation;
    for (int i = 0; i < n; i++) {
      int pi; cin >> pi;
      permutation.push_back(pi);
    }
    string s; cin >> s; // black0 or white1

    // for memoization
    vector<int> blackCounters(n, -1); // -1 means we dont know yet

    for (int i = 1; i <= n; i++) {
      // calculate F(i) and print it

      if (blackCounters[i-1] != -1) {
        // already computed
        cout << blackCounters[i-1] << " ";
        continue;
      }
      
      unordered_set<int> visited;
      stack<int> backtrackStack;

      int currentI = i;
      int cycleRepeatNumber;
      // follow through with the pattern and find the cycle
      bool memoizeCase = false;
      while (true) {
        currentI = permutation[currentI-1];
        if (blackCounters[currentI-1] != -1) {
          // already computed at currentI
          memoizeCase = true;
          backtrackStack.push(currentI);
          break;
        }
        
        if (visited.count(currentI) != 0) {
          cycleRepeatNumber = currentI; // do not add to stack because already visited
          break;
        }

        backtrackStack.push(currentI);
        visited.insert(currentI);
      }

      // if not memoize case: there is a cycle for sure

      int blackCounter = 0;
      if (!memoizeCase) {

        // go through the cycle backward to find start point
        queue<int> cycleNums; // keep track of nums in the cycle so we can memoize their blackCounters
        while (true) {
          currentI = backtrackStack.top();
          backtrackStack.pop();

          // add to black counter (inclusive of the start of the cycle)
          if (s[currentI-1] == '0') blackCounter++;
          cycleNums.push(currentI);

          if (currentI == cycleRepeatNumber) {
            // reached the beginning of the cycle
            break;
          }
        }

        // set everything in the cycle's black counter
        while (!cycleNums.empty()) {
          int cycleNum = cycleNums.front();
          cycleNums.pop();
          blackCounters[cycleNum-1] = blackCounter;
        }

      }

      // now everything remaining in backtrackStack is outside the cycle
      
      // if memoize case: same as not memoized except we skip finding the cycle and we start black counter at the memoized value
      if (memoizeCase) {
        int memoizeNum = backtrackStack.top();
        backtrackStack.pop();
        blackCounter = blackCounters[memoizeNum-1];
      }

      // go through the rest of the numbers and write to their black counters 
      while (!backtrackStack.empty()) {
        int num = backtrackStack.top();
        backtrackStack.pop();

        if (s[num-1] == '0') blackCounter++;

        blackCounters[num-1] = blackCounter;
      }

      // this should exist now
      cout << blackCounters[i-1] << " ";
    }

    cout << "\n";
  }
}