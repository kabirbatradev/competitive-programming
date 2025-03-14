// LLM generated code (with some guidance)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  int n;

  Solution() {
    cin >> n;  // num gates

    vector<int> roadFee(n - 1);
    for (int i = 0; i < n - 1; i++) {
      cin >> roadFee[i];
    }

    int maxTime = 0;
    vector<int> openingTimes(n);
    for (int i = 0; i < n; i++) {
      cin >> openingTimes[i];
      maxTime = max(maxTime, openingTimes[i]);
    }

    // Add dummy gate
    n++;
    roadFee.push_back(0);
    openingTimes.push_back(0);  // Dummy gate is always open

    // We need enough time to potentially visit all gates with some back and
    // forth
    int timeSize = maxTime + 2 * n;

    // Initialize dp with a large value
    const ll INF = 1e18;
    vector<vector<ll>> dp(n, vector<ll>(timeSize, INF));

    // Base case: We start at gate 0, time 0, with cost 0
    dp[0][0] = 0;

    // Fill the DP table
    for (int time = 0; time < timeSize - 1; time++) {
      for (int gate = 0; gate < n; gate++) {
        if (dp[gate][time] == INF) continue;

        // Try moving forward
        if (gate < n - 1) {
          int nextGate = gate + 1;
          int nextTime = time + 1;

          if (nextTime >= openingTimes[nextGate]) {
            // Gate is open, we can pass through
            dp[nextGate][nextTime] =
                min(dp[nextGate][nextTime], dp[gate][time] + roadFee[gate]);
          } else {
            // Gate is closed, turn back immediately
            // We spend 2 time units total: 1 to go forward and 1 to come back
            dp[gate][time + 2] =
                min(dp[gate][time + 2], dp[gate][time] + 2 * roadFee[gate]);
          }
        }

        // Try moving backward
        if (gate > 0) {
          int nextGate = gate - 1;
          int nextTime = time + 1;
          dp[nextGate][nextTime] =
              min(dp[nextGate][nextTime], dp[gate][time] + roadFee[gate - 1]);
        }
      }
    }

    // Find the minimum cost to reach the dummy gate (n-1)
    ll minCost = INF;
    for (int time = 0; time < timeSize; time++) {
      minCost = min(minCost, dp[n - 1][time]);
    }

    cout << minCost << endl;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}
