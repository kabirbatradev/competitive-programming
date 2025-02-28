
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(1); // # decimal places
  // cout << fixed; // force precision decimal places
  
  int n; cin >> n;

  vector<int> price(n);
  for (int i = 0; i < n; i++) {
    cin >> price[i];
  }

  // vector of size 2 arrays
  vector<vector<int>> dp(n, vector<int>(2));
  // base case: 
  dp[0][true] = -price[0];
  dp[0][false] = 0;
  // compute:
  for (int i = 1; i < n; i++) {
    int a = dp[i-1][true];
    int b = i-2 >= 0 ? dp[i-2][false] : 0;
    dp[i][true] = 
      max(a, b - price[i]);
    dp[i][false] = 
      max(dp[i-1][false], dp[i-1][true] + price[i]);
  }

  // answer is after all nums considered, after no stock in hand
  cout << dp[n-1][false] << '\n';

}

/*
given list of stock price per day
restrictions:
can only hold one stock
if sell today, cannot buy tomorrow!

greedy does not work because
want to buy at low point (right before an increase)
want to sell at high point (right before a decrease)
if we sell at the highest point,
  but the next num is a low point
  then we cannot buy at that low point, but rather forced to ignore it

dp alternative:
  thinking about dp (incomplete idea):
  dp[i] means 
    best solution (money made) 
    up to stock price i being considered (inclusive)
  dp[i] =  
    dp[i-1] if we do not buy on this day=i
    dp[i-2] if we want to buy at this day=i

  how do we know whether we are holding a stock or not?
  new dp idea with bool "holding stock"
  dp[i][holding] means 
    best solution (money made) 
    up to stock price i being considered (inclusive)
    holding = true means we have a stock in hand
    holding = false means we have no stock, we can buy
  dp[i][holding=true] =  
    either we bought on this day, 
      but then how would we know if we sold yesterday? i want more 
      information inside of "holding"
    or we already had stock

  new dp idea where "holding" tells us how recently we sold as well
  dp[i][holding] means 
    best solution (money made) 
    up to stock price i being considered (inclusive)
    holding = HAVE_STOCK = 0 means we have a stock in hand
    holding = JUST_SOLD = 1 means we have no stock, but we just sold, so we cannot buy tomorrow
      dont need this actually! just look back 2 days
    holding = NO_STOCK = 2 means we have no stock and we sold yesterday or later in the past, allowing us to buy tomorrow
  how to get dp[i][HAVE_STOCK]:
    either we already had stock or we just bought today
    dp[i-1][HAVE_STOCK] = yesterday and had stock
    dp[i-1][NO_STOCK] = yesterday and no stock
      or we could just look back 2 days 
      then holding can be a boolean again!
      dp[i-2][NO_STOCK] = 2 days ago we had no stock, and now we can buy
      what if i-2 doesnt exist? then use 0 = earnings with no stock
    formula: dp[i][HAVE_STOCK] = 
      max(dp[i-1][HAVE_STOCK], dp[i-2][NO_STOCK] - price[i])
  how to get dp[i][NO_STOCK]:
    either we dont have stock already or we had but sold today
    dp[i-1][NO_STOCK] = yesterday no stock
    dp[i-1][HAVE_STOCK] = yesterday with stock, want to sell today
    formula: dp[i][NO_STOCK] = 
      max(dp[i-1][NO_STOCK], dp[i-1][HAVE_STOCK] + price[i])
  
  final formula: (HAVE_STOCK is a bool)
  formula: dp[i][HAVE_STOCK] = 
    max(dp[i-1][HAVE_STOCK], dp[i-2][NO_STOCK] - price[i])
  formula: dp[i][NO_STOCK] = 
    max(dp[i-1][NO_STOCK], dp[i-1][HAVE_STOCK] + price[i])
  base case:
    dp[0][true] means after first day, with stock, 
      money = -price[0]
    dp[0][false] means after first day, with no stock,
      money = 0

*/