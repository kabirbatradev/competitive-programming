// Author: Kabir Batra
// It is okay to share my code for educational purposes
// Note: no gen AI was used for this problem

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  int n;

  Solution() {
    cin >> n; // num gates 

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

    // dummy gate:
    n++;
    roadFee.push_back(0);
    openingTimes.push_back(INT_MAX);
    
    // worst case time: max gate time + # gates if we are waiting at the first gate still 
    // + 1 if we had to do a u-turn at the start i guess?
    int timeSize = maxTime + n + 1;

    // lets create a map 
    // maybe a vector of vectors (one for each time)? nvm
    // key = (position/gate we are at, time)
    // value = optimal fee
    map<pair<int, int>, int> dp;

    // if we wanted to do vector of vectors:
    // index = time
    // returned vector is list of:
      // index is position
      // value is optimal cost
    // vector<vector<int>> dp(timeSize);

    // for time = 0: to get to gate 0, it costs nothing
    dp[{0, 0}] = 0;
    // dp[0].push_back(0); 

    int maxPosPrevTime = 0;

    // for every new time t, lets push things into dp using values from prev time
    for (int t = 1; t < timeSize; t++) {
      // for every position accessable in previous time, 
      // go forward or backward if possible, and use that to generate dp at current time

      // itereate through every pos for previous time
      for (int pos = 0; pos <= maxPosPrevTime; pos++) {
        auto it = dp.find({pos, t-1});
        if (it == dp.end()) {
          // this pos is not set in the previous dp table, so just skip (we cant build on it)
          continue;
        }

        int currentCost = it->second;

        // otherwise, we have a state (pos, t-1) that we can build from
        // want to set these two values:
        // dp[{pos-1, t}] = ...
        // dp[{pos+1, t}] = ...
        // note: 
          // they could be out of bounds (then skip)
          // pos-1 might already be set, so then overwrite it only if we have something smaller
        
        // if pos-1 is not out of bounds
        if (pos-1 >= 0) {

          // full cost = cost to get to pos + cost to travel on the road
          int fullCost = currentCost + roadFee[pos-1]; // same index for road and gate gives us road right after


          auto it2 = dp.find({pos-1, t});
          if (it2 != dp.end()) {
            // this entry in the table already exists
            int cost = it2->second;
            if (fullCost < cost) {
              it2->second = fullCost; // should update the cost value in the map
            }
          }
          else {
            // the entry is not already in the table, so just set it
            dp[{pos-1, t}] = fullCost;
          }
        }


        // if pos+1 is not out of bounds
        if (pos+1 < n) {

          // before writing this new position, note that we cannot go to pos+1 unless:
          // the gate pos is open at time = t-1
          if (t-1 < openingTimes[pos]) {
            continue;
          }

          // full cost = cost to get to pos + cost to travel on the road
          int fullCost = currentCost + roadFee[pos]; 
          dp[{pos+1, t}] = fullCost; // no chance that this is already set

          maxPosPrevTime = max(maxPosPrevTime, pos+1);

        }
      }
      // finished iterating through all positions for previous time



      // some vector ideas:

      // dp[t] = vector<int>(dp[t-1].size())

      // for (int pos = 0; pos < dp[t-1].size(); pos++) {
        


      //   // considering (pos, t-1)
      //   int cost = dp[t-1][pos];

      //   // if going backward is not out of bounds:
      //   if (pos-1 >= 0) {
          
      //   }

      // }
    }

    // now that we have gone through every time:
    // we can iterate through every time, and set pos to the fixed value of n-1
      // this requests how much it costs to reach the dummy gate in a certain amount of time
    int minCost = INT_MAX; // running min
    for (int t = 0; t < timeSize; t++) {

      auto it = dp.find({n-1, t});
      // if its in the table, then update min cost
      if (it != dp.end()) {
        int cost = it->second;
        minCost = min(minCost, cost);
      }
    }
    // print the running min
    cout << minCost << '\n';
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
  get through the last gate

approach: dp 
  state: 
    gate reached
    time it took to reach
  note: we can reach a gate, but it is closed, and then we have to turn back
    therefore, reaching the last gate doesnt mean the problem is solved
    solution: create a new dummy gate after the last one
      make the cost of the road 0 
      make the opening time INT_MAX (it never opens, but that shouldnt matter)
      if we can reach that dummy gate, then we have successfully passed through the last gate
  dp[state] = ?
    should return the optimal cost of getting to that gate in that much time
  how to set every dp[state]:
    can go over all positions we could reach at t-1
    and then go forward or backward from that position
    and set dp[new pos][t]
use hashmap so we dont have a super large array that is potentially quite scarce


*/