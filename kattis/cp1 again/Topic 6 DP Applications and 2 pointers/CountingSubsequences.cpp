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
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }



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

prefix sum idea:
  create prefix sum of whole array
  do something like the 2d matrix sum idea

  if prefix[i] = sum of all elements inclusive of i,
  sum of a subarray
*/