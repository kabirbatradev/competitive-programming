#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int T; cin >> T;

  for (int tc = 0; tc < T; tc++) {
    cin.get();
    
    int n; cin >> n;
    // vector<int> nums(n);
    vector<pair<int,int>> prefixSums; 
    prefixSums.reserve(n+1); 

    prefixSums.push_back(make_pair(0, 0)); // additional 0 sum 
    for (int i = 0; i < n; i++) {
      int numi;
      cin >> numi;
      prefixSums.push_back(make_pair(prefixSums.back().first + numi, i+1));
    }

    
    sort(prefixSums.begin(), prefixSums.end()); // should sort by prefix sum value itself
    int count = 0;
    int l = 0, r = 0; // 2 pointers
    while (r < prefixSums.size() && l < prefixSums.size()) {
      if (prefixSums[r].first - prefixSums[l].first == 47) {
        // only valid subarray if r prefix sum came after l prefix sum
        // if (prefixSums[r].second > prefixSums[l].second) {
        //   count++;
        // }
        // l++; 
        // issue: there could be duplicate values on the left or on the right, and we need to count all of them
        // one potential solution: check all possibilities pushing left pointer that are still valid, and then reset left pointer
        // and push right pointer
        int l2 = l;
        while (prefixSums[r].first - prefixSums[l2].first == 47) {
          if (prefixSums[r].second > prefixSums[l2].second) {
            count++;
          }
          l2++;
        }
        r++;

      }
      // too big: push left pointer
      else if (prefixSums[r].first - prefixSums[l].first > 47) {
        l++;
      }
      // too small: push right pointer 
      else {
        r++;
      }
    }

    cout << count << '\n';
  }
}

/*
create prefix sum
sort prefix sums but keep track of the index that that prefix sum used to be at
use 2 pointers over the prefix sums
  prefix sums subtracted = sum of a subarray
  if the difference is too large, then push left pointer; otherwise push right pointer
    note: right pointer index has to be larger index
    only allow sums where the right prefix sum index > left prefix sum index

my own test case for duplicate prefix sums:
5
-20 20 40 7 0



*/