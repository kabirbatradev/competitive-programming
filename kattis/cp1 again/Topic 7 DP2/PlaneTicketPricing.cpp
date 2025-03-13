// Author: Kabir Batra
// It is okay to share my code for educational purposes
// Note: no gen AI was used for this problem

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  vector<vector<pair<int, int>>> weekData;
  int firstWeekTicketPrice = -1;

  int n, w;

  Solution() {
    cin >> n >> w; 
    // num seats left, num weeks left

    weekData = vector<vector<pair<int, int>>>(w+1);

    for (int i = w; i >= 0; i--) {
      int k; cin >> k; // # prices to consider
      weekData[i] = vector<pair<int, int>>(k);
      for (int j = 0; j < k; j++) {
        cin >> weekData[i][j].first; // store price in first
      }
      for (int j = 0; j < k; j++) {
        cin >> weekData[i][j].second; // store # tickets sold at that price in second 
      }
    }

    int revenue = dfs(w, n);
    cout << revenue << '\n';
    cout << firstWeekTicketPrice << '\n';
  }

  // cache: takes in state, and returns max revenue
  map<pair<int, int>, int> cache;

  int dfs(int weeksLeft, int seatsLeft) {
    // base case: # seats left = 0, or # weeks left is -1
    if (seatsLeft == 0 || weeksLeft == -1) {
      return 0; // we cannot make any money from these cases
    }

    // check cache
    auto it = cache.find(make_pair(weeksLeft, seatsLeft));
    if (it != cache.end()) {
      return it->second; // pair of key value, value is at 'second'
    }

    // try every price at this week
    // and remember the best one
    int maxRevenue = 0;
    int priceSoldToGetMaxRevenue = INT_MAX;
    for (auto [price, numTicketsSold] : weekData[weeksLeft]) {
      // only sell up to # tickets left
      numTicketsSold = min(numTicketsSold, seatsLeft);
      // how much money would be made if we took this path:
      int revenue = price * numTicketsSold;
      // add the money made from an optimal subproblem
      revenue += dfs(weeksLeft-1, seatsLeft - numTicketsSold);
      
      if (revenue > maxRevenue) {
        maxRevenue = revenue;
        priceSoldToGetMaxRevenue = price;
      }
      // case where revenue is same: we want to remember smaller price
      else if (revenue == maxRevenue && price < priceSoldToGetMaxRevenue) {
        priceSoldToGetMaxRevenue = price;
      }
    }

    // if this was the first week, set global
    if (weeksLeft == w) {
      firstWeekTicketPrice = priceSoldToGetMaxRevenue;
    }

    // store in cache
    cache[make_pair(weeksLeft, seatsLeft)] = maxRevenue;

    return maxRevenue;

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
what if we complete search/brute force/dfs:
  at every week, try every price
  then go to the next week with the new # seats that exist
  repeatedly ask, what is the money we will make with:
    w weeks left
    s seats left
  note that w and s define the current "state"
are there overlapping subproblems?
  rephrased: can we reach the same state from 2 different paths?
  yes: we can reach w weeks left and s seats left by selling
    different amounts in the past weeks, but they add up
    to the same # of seats sold
therefore, we can use caching (and this is a dp problem)

top down function: get optimal revenue given # weeks left and # seats remaining
  if there are w weeks left,
  go through all of the potential prices we could assign to that week
  call function on -1 weeks left, - certain number of seats left
  take the max one for max revenue
  return that max revenue

  also, if weeks left == w, then this is the current week
  so we can assign some global variable to 
  the ticket price we assigned that got us the best score
    smallest ticket price if there is a tie
*/