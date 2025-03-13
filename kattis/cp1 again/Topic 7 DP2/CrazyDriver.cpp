// Author: Kabir Batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int n; cin >> n; // num gates 

    vector<int> roadFee(n-1);
    for (int i = 0; i < n-1; i++) {
      cin >> roadFee[i];
    }

    int maxTime = 0;
    vector<int> openingTimes(n);
    for (int i = 0; i < n; i++) {
      cin >> openingTimes[i]; 
      maxTime = max(maxTime, openingTimes[i]);
    }

    // # positions = # gates = n
    // # times = max gate time + # gates if we are waiting at the first gate still + 1 if we had to do a u-turn i guess?
    // initialize dp values to INT_MAX to show impossible
    int timeSize = maxTime + n + 1;
    vector<vector<int>> dp(n, vector<int>(maxTime + n + 1, INT_MAX));

    // set the first dp value: at state (pos=0, time=0), cost = 0
    dp[0][0] = 0;

    // for the next time step, write optimal answer for gates we can reach
    for (int t = 1; t < timeSize; t++) { // starting at time = 1 because we already did time = 0
      for (int pos = 0; pos < n; pos++) {
        // want to set dp[pos][t] = ...

        // consider coming from next gate or prev gate
        // note that next or prev pos might not exist!
        // also note that we could have only come from the previous gate if the previous gate is open
          // specifically, if we want to go through the pos-1 gate, it had to be open 1 hr ago (or earlier), such that we could be at pos at current t
        // dont have to do this check for "from next" because we could only have been there if all prev gates are already open
        int fromNext = INT_MAX, fromPrev = INT_MAX;
        if (pos+1 < n) {
          fromNext = dp[pos+1][t-1];
          if (fromNext != INT_MAX) fromNext += roadFee[pos]; // add toll of road after pos
        }
        if (pos-1 >= 0 && openingTimes[pos-1] <= t-1) {
          fromPrev = dp[pos-1][t-1];
          if (fromPrev != INT_MAX) fromPrev += roadFee[pos-1]; // add toll of road before pos
        }

        // now store the best answer (min cost)
        dp[pos][t] = min(fromNext, fromPrev);

      }
    }

    // print the entire dp table:
    for (int t = 0; t < timeSize; t++) {
      cout << "t = " << t << ":\t";
      for (int pos = 0; pos < n; pos++) {
        cout << (dp[pos][t] != INT_MAX ? to_string(dp[pos][t]) : "--") << "\t";
      }
      cout << endl;
    }
    cout << endl;

    
    // get best dp at gate n: pos=(n-1)
    int cheapest = INT_MAX;
    for (int t = 0; t < timeSize; t++) { // consider all times
      cheapest = min(cheapest, dp[n-1][t]);
    }

    cout << cheapest << '\n';

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
problem statement summary:
  n gates
  n-1 roads between, each with a fee
  for each gate, there is a time when it "opens" to cross through

goal: 
  pay minimum toll fee
how would human solve it?
  drive to first gate
  if its not open, then we have to drive back (pay for first road again)
  and then drive back to first gate (pay for first road again)
  eventually we decide to go from first to second gate (and pay for second road)
  if future gates are not open yet, it might be optimal to just go back and forth
    on a cheap road and wait for all the gates to open
  could it be better to go back and forth on an expensive gate to quickly get to a super cheap gate?
    only want to wait on a cheap road until you can just barely make it to the new cheap road
    while going through expensive roads only once

dp idea:
  state = (current gate position, amount of time passed) = (pos, time)
  output = optimal money on road tolls spent
dp recursive equation concept:
  to get the cheapest price to get to a certain state (pos, time),
  we could only have come from next or prev gate, and only from prev time
    query next gate (pos+1, time-1)
    query prev gate (pos-1, time-1)
    add toll price
    skip a gate if its not open
    take optimal solution from there
Q: how do we make sure prev state exists?
  just make sure all possible (pos, time) are set for t-1 specifically
  maybe set $ = INTMAX for impossible
  there are n gates, so we would have to set n values per iteration
    we could also use a map that stores only gates that we were able to reach
represent DP states:
  2d vector which takes in pos and time
  # positions = # gates = n
  # times = max gate time + # gates if we are waiting at the first gate still + 1 if we had to do a u-turn i guess?

Q: where is solution stored?
  dp[pos = nth gate = (n-1)][time = ?]
  i guess we should go through all times at the end and get min

alternatively, if we used a map instead, should we stop when we reach the final gate?
  could we have a better solution if we got to the final gate later than the fastest time? probably...
*/