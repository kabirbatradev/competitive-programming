#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

int prefix[50'001]; // maybe the vectors were taking too long to make?

struct Solution {
  Solution() {
    int d, n; cin >> d >> n;
    // d is divisor 

    // map from remainder to count
    map<int, int> hist;

    // vector<int> prefix(n+1); // sum of all elements include this
    prefix[0] = 0;
    hist[0]++;
    int counter = 0;
    for (int i = 0; i < n; i++) {
      int num;
      cin >> num;
      prefix[i+1] = (prefix[i] + num) % d;
      // can mod in advance to not overflow?

      // what we we want in order to be divisble?
      // prefix j - prefix i must be divisble 
      // if prefixj = 0, then we want prefixi = 0
      // let d = 5
      // if prefixj = 3 --> 8
      // then we want prefixi = 3, to get to 5
      // such that subtracting them gives u 0 

      counter += hist[prefix[i+1]];

      hist[prefix[i+1]]++;
    }

    // go though every subsequence: start, end
    // start 0 means no elements
    // end 1 means include the first num
    // end = n means include the last number
    // int counter = 0;
    // for (int i = 0; i < n+1; i++) {
    //   for (int j = i+1; j < n+1; j++) {
    //     if ((prefix[j] - prefix[i]) % d == 0) {
    //       counter++;
    //     }
    //   }
    // }
    cout << counter << '\n';
  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  int t; cin >> t;
  for (int i = 0; i < t; i++) 
    Solution s;
}

/*
given list of nums
find all contiguous subsequences
that are divisible by some number
use prefix sums
to get contiguous subsequence sums

WHY TLE?
i switched to array but still TLE
maybe double for loop to construct every possible subseqeunce was not the move?
every pair of nums is too slow

how can we do one pass:
idk
keep a count of all the prefix sums so far that are alr divisible by smth
keep count for basically every remainder 
like a histogram map

*/