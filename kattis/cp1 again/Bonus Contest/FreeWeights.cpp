#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  int n; 

  vector<int> weights1;
  vector<int> weights2;

  Solution() {
    cin >> n;

    // vector<int> weights1(n);
    weights1.resize(n);
    set<int> nums;
    for (int i = 0; i < n; i++) {
      cin >> weights1[i];


      // remove if alr there
      if (nums.contains(weights1[i])) {
        nums.erase(weights1[i]);
      }
      else {
        nums.insert(weights1[i]);
      }
      // add if not there
    }

    // if theres anything in set, then thats a guaranteed move dumbell
    int worst = 0;
    for (int badDumbell : nums) {
      worst = max(worst, badDumbell);
    }


    // read in second row
    weights2.resize(n);
    // vector<int> weights2(n);
    for (int i = 0; i < n; i++) {
      cin >> weights2[i];
    }


    // now BSTA: 
    int low = worst;
    int high = 10e9; // max weight dumbell

    int best = high;

    while (low <= high) {
      int mid = low + (high - low) / 2;

      bool success = canFunction(mid);
      
      // can do lower weight
      if (success) {
        high = mid-1;
        best = min(best, mid);
      }
      else {
        low = mid+1;
      }
    }

    cout << best << '\n';


  }

  // we could honestly just merge arrays lol
  int canFunction(int canCarry) {
    int prev = -1;
    for (int i = 0; i < n; i++) {


      if (weights1[i] <= canCarry) continue;


      if (prev == -1) {
        prev = weights1[i];
      }
      else {
        if (prev == weights1[i]) prev = -1; // set back to -1 if match
        else {
          return false; // fail if not 2 in a row are same
        }
      }
    }

    // do same for second array
    prev = -1;
    for (int i = 0; i < n; i++) {
      if (weights2[i] <= canCarry) continue;
      if (prev == -1) {
        prev = weights2[i];
      }
      else {
        if (prev == weights2[i]) prev = -1;
        else {
          return false;
        }
      }
    }

    return true;
  }


};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
dumbells
on rack
Output the weight of the heaviest dumbbell that must be moved
if dumbell on separate racks, then def have to move

then BSTA for worst dumbell u have to move
ignore all dumbells smaller weight
goal is to see if all other dumbells are in pairs
*/