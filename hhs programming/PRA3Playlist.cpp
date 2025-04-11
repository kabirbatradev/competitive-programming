#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n, k; cin >> n >> k;

    // (beauty, length)
    vector<pair<int, int>> songs(n);

    // read in songs, populate array
    for (int i = 0; i < n; i++) {
      int t, b; cin >> t >> b; // length and beauty

      songs[i] = {b, t};
    }

    // sort with max beauty first, subsort by max length first
    sort(songs.begin(), songs.end(), greater<pair<int, int>>());

    // iterate through songs, sliding window represented with min heap of song lens
    priority_queue<int, vector<int>, greater<int>> pq;
    // int prevBeauty = songs[0].first;
    int currentLengthSum = 0;
    int best = 0;
    for (auto [beauty, length] : songs) {

      // add new song to set
      pq.push(length);
      currentLengthSum += length;

      // remove min song
      if (pq.size() > k) {
        currentLengthSum -= pq.top();
        pq.pop();
      }

      // assume min beauty is 'beauty' because songs are sorted by beauty and it only gets worse
      best = max(best, beauty * currentLengthSum);
    }

    cout << best << '\n';
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
goal: find combination of songs (max size k) such that total length * min(beauty) is maxed out

brute force: try every combination of k or less songs

greedy: want to use longest songs, but also want to use higher beauty

BSTA-like approach: 
  input: min beauty allowed
  question: what are the longest k songs with this min beauty
    can sort songs, skip if their beauty is too long
  this isnt a can function though...

what if we sorted by:
  max beauty first
  longer song length first 
then we can do something like sliding window:
  find best solution for first max beauty 
  can put items into pq with weight = song length

  when stepping down to worse beauty: 
    can still use higher beauty items
    kick them out of pq if there are songs shorter than new songs of the worse beauty
  
  pq should be min heap, so we can delete min element if size > k

*/