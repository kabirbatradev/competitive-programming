#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int n, m; cin >> n >> m; // m lane numbers
  int k, r; cin >> k >> r;

  vector<int> len(n, 0); // n straights, initialize to make sure no undefined
  for (int i = 0; i < n; i++) {
    cin >> len[i];
  }
  vector<pair<int, int>> sAndC(n-1, make_pair(0,0)); // n-1 curves, initialize to make sure no undefined
  for (int i = 0; i < n-1; i++) {
    cin >> sAndC[i].first >> sAndC[i].second;
  }

  // add a new dummy curve at the end:
    // s = 0, c = 0
  sAndC.push_back(make_pair(0, 0));

  vector<vector<ll>> dp(n+1, vector<ll>(m, INT_MAX));

  // base case: before any curve or straight
  dp[0][0] = 0;
  // everything else of the base case is INT_MAX

  // set dp at curveNum, i=lane
  // (n-1)+2 because
    // n-1 curves in total
    // 0 case is skipped
    // extra dummy curve
  for (int curveNum = 1; curveNum < n+1; curveNum++) {
    for (int i = 0; i < m; i++) {

      // consider starting at every lane
      for (int j = 0; j < m; j++) {
        int numLaneChanges = abs(i - j);

        // skip if numLaneChanges is impossible
        // use length of straight before this curve
        if ((len[curveNum-1] / k) < numLaneChanges) {
          continue;
        }
        // skip if impossible 
        if (dp[curveNum-1][j] == INT_MAX) {
          continue;
        }

        dp[curveNum][i] = min(
          dp[curveNum][i], // current value, INT_MAX initially
          dp[curveNum-1][j] + numLaneChanges * r
        );

      }
      
      // now, if not impossible, add constants (curve dist, straight dist)
      // auto [s, c] = sAndC[curveNum-1]; introduced in cpp 17
      int s = sAndC[curveNum-1].first; 
      int c = sAndC[curveNum-1].second; 
      // -1 because, curveNum starts at 1 but we would want the first data point
      int actualLaneNum = i+1;
      ll curveDist = s + c * actualLaneNum;
      if (dp[curveNum][i] != INT_MAX) {
        dp[curveNum][i] += curveDist + len[curveNum-1];
      }


      // if (i == 0) {
      //   cout << curveNum << ": " << dp[curveNum][i] << endl;
      //   cout << "curveDist: " << curveDist << endl; 
      // }
    }
  }

  // (n-1)+2 = n+1 states in total
    // we added dummy curve 
    // 0 is before the first curve
  // so we should index at n
  cout << dp[n][0] << '\n'; // want lane 1 which means i = 0

}

/*
every straight way, we can maybe switch a lane or a few
  can do len / k lane changes
  but it costs an additional r distance per lane change
between each straight, we have a curve:
  distance traveled over curve = s + c * lane number 

dp solution:
  state:
    curveNum = the current curve number that we just finished going through
    i = the lane # that we ended the curve at
  dp returns distance traveled after reaching that state
  compute dp[curveNum][i] by:
    consider where we could have been during the previous curveNum
    for every lane j that we could have been at
      attempt to move to lane i using the straight that is in between
      skip if not possible (mark as INT_MAX if impossible)
      additional distance traveled = change amount * k
    only use the minimum one!
    then add the curve travel distance for this lane i
      = s + c * i 
  formula: dp[curveNum][i] = 
    min(
      dp[curveNum-1][consider every j] + num lane changes * k
    )
    + s + c * i 
  formula tells u distance traveled at the end of the curveNum curve

  base case: 
    dp[0] can be "no curves"; we can make things 1 indexed
    dp[0][lane #0] = 0
    dp[0][all other lane numbers] = INT_MAX which means its impossible
    note i assume lanes are actually 0 indexed
  final answer:
    dp[n] = distance traveled after completing last curve
    so lets add a new curve at the end of the last straight:
      s = 0, c = 0
    then we can get distance traveled guaranteeing we reached
      lane 0 (aka lane 1) while on the last straight using:
      d[n+1][lane# 0]
  
  summary:
  add a new dummy curve at the end:
    s = 0, c = 0
  formula: dp[curveNum][i] = 
    min(
      dp[curveNum-1][consider every j] + num lane changes * r
    )
    + s + c * i 
  base case: 
    dp[0][lane #0] = 0
    dp[0][all other lane numbers] = INT_MAX which means its impossible
  final answer:
    dp[n+1][lane# 0]

  what if # num lane changes is not possible?
    can do len / k lane changes
    if not possible, then skip
  where do we add straight's len?
    add previous straight len to current curve len
  
  i used LONG_MAX instead of LLONG_MAX
  and i was missing a check for LONG MAX and added something
    but on my computer it did not overflow (maybe it was treated as INT MAX)
    but on linux, it overflowed and gave wrong answer (because it was treated as long long)
  
*/