#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  // ll mod = (ll)10e9 + 7;
  ll mod = 1e9 + 7;
  // cout << mod << endl;
  // cout << 8000040628 % mod << endl;
  // return 0;

  int n, x; cin >> n >> x;

  vector<int> coins(n);
  for (int i=0; i < n; i++) {
    cin >> coins[i];
  }
  sort(coins.begin(), coins.end()); // sort in increasing order
  // for (int i=0; i < n; i++) {
  //   cout << coins[i] << " ";
  // }

  // dp table: dp[i][j], returns number of ways
  // i is the target sum of money
  // j is the index of the last coin used (only allowed to build on this with coins of equal or larger index aka larger coins)
  // int dp[x+1][n] = {0};
  vector<vector<ll>> dp(x+1, vector<ll>(n, 0));

  // set base cases: using a single coin
  for (int j = 0; j < n; j++) {
    if (coins[j] > x) continue;
    dp[coins[j]][j] = 1;
  }

  for (int i = 0; i <= x; i++) {
    for (int j = 0; j < n; j++) {
      // cout << dp[i][j] << " ";

      // we must have coin j be at the end of the sequence
      // i: request dp at sum = i-coins[j]
        // make sure this is at least 0, otherwise, ig this dp value is 0
      // j: with the sequence ending with any number smaller or equal to j current j
      // sum those together to get dp[i][j]

      if (i-coins[j] < 0) continue;

      for (int smallerJ = 0; smallerJ <= j; smallerJ++) {
        dp[i][j] = (dp[i][j] + dp[i-coins[j]][smallerJ]) % mod;
      }
      
    }
    // cout << endl;
  }

  ll total = 0;
  // for every last coin used, get number of ways to get to x
  for (int j = 0; j < n; j++) {
    total = (total + dp[x][j]) % mod;
  }

  cout << total << endl;

  return 0;
}