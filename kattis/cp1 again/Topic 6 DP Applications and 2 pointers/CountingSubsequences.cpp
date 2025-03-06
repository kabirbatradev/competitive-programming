// Author: Kabir batra
// It is okay to share my code for educational purposes

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
    vector<int> nums(n);
    vector<int> prefixSum; 
    prefixSum.reserve(n+1); 

    unordered_map<int, vector<int>> m; // prefix sum --> vector of indices
    prefixSum.push_back(0); // additional 0 sum 
    m[0].push_back(0); // corresponding map entry
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
      prefixSum.push_back(prefixSum.back() + nums[i]); // note that the index of this prefix sum is off by 1
      m[prefixSum.back()].push_back(i+1); // at the new prefix sum value, push back the index
    }

    int count = 0;

    // for every prefix sum (skip the first '0' sum), find past prefix sums that would reach target
    const int target = 47;
    for (int i = 1; i < n+1; i++) {
      // example for debugging:
      // printf("index = %d, prefix sum value: %d\n", i, prefixSum[i]);

      // for every prefix sum (index) that matches the value we need
      for (int index : m[prefixSum[i] - target]) {
        if (index > i) break; // we cannot use prefix sums that come later
        // example for debugging:
        // printf("  found matching prefix sum at %d with value %d, subtracting prefix sums gets you %d\n", index, prefixSum[index], prefixSum[i] - prefixSum[index]);
        count++;
      }
    }

    cout << count << '\n';
  }
}

/*
sliding window doesnt work because:
  we cant greedily push right pointer if we are too small 
  because right pointer might have negative number which makes the 
  sum smaller

brute force:
  try every continuous subarray

one dp idea:
  i = index where a subsequence ended
  j = sum of subsequence
  dp[i][j] = # of ways to make subsequences that sum to j, 
    where the subsequence ends at i itself (inclusive)
  dp[i][j] formula: (for every i, do this)
    iterate through every dp[i-1] = map of sum=j --> count
    set a bunch of dp[i][j = previous j + num[i]]

prefix sum hint:
  create prefix sum of whole array
  do something like the 2d matrix sum idea?

  if prefix[i] = sum of all elements inclusive of i,
  sum of a subarray [i, j] = prefix[j] - prefix[i-1]

prefix sum idea:
  put prefix sum values into hashmap: sum --> index
    since there can be duplicates, sum --> vector of indices (sorted automatically because of order of insertion)
  2 sum (not sorted) approach: 
    for every later prefix sum, ask the hashmap if the corresponding earlier prefix sum exists: later prefix - earlier prefix = 47 (the target)
*/