// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int d; cin >> d;

  vector<int> prices;
  prices.reserve(d);
  int prev = -1;
  for (int i = 0; i < d; i++) {
    int price; cin >> price;

    // remove back to back duplicates
    if (price != prev) {
      prices.push_back(price);
      prev = price;
    }
  }

  // if all prices are the same
  if (prices.size() == 1) {
    // dont buy anything, just keep your $100 till the end
    cout << 100 << '\n';
    return 0;
  }


  // initialize values for day 0 -> 1 case
  ll currMoney = 100;
  ll bestMoney = 100;
  ll currStocks = 0;

  // assume decreasing from the beginning
  // so that we buy only when price starts to increase
  bool currentlyIncreasing = false;

  for (int i = 0; i < prices.size()-1; i++) {
    // increasing
    if (prices[i] < prices[i+1]) {
      // if already increasing, then nothing changed
      if (currentlyIncreasing) continue;
      currentlyIncreasing = true;
      // if switched from decreasing to increasing, 
      // then we have a minimum at day i
      // so we buy as much as possible at day i

      // cout << "buy at price " << prices[i] << endl;
      currStocks = currMoney / prices[i];
      // but wait! we can't buy more than 100,000 shares!
      if (currStocks > 100000) currStocks = 100000;
      currMoney -= currStocks * prices[i];

    }
    // decreasing
    else if (prices[i] > prices[i+1]) {
      // if alr decreasing, then nothing changed
      if (!currentlyIncreasing) continue;
      currentlyIncreasing = false;
      // if switched to decreasing, 
      // then we have a peak at day i
      // so we sell everything
      // cout << "sell at price " << prices[i] << endl;
      currMoney += currStocks * prices[i];
      currStocks = 0;

      // also update best money
      bestMoney = currMoney;
    }
    else {
      // should never happen because we removed back to back duplicates
    }
  }
  // note: we did not consider the last day
  // if we were increasing, then last day is a peak, so we should sell
  if (currentlyIncreasing) {
    // cout << "sell at price " << prices.back() << endl;
    currMoney += currStocks * prices.back();
    currStocks = 0;

    // also update best money
    bestMoney = currMoney;
  }

  // use best money instead of current 
  // because we might have bought stocks and then the days ended
  // and the price kept decreasing so we still have stock in hand
  cout << bestMoney << '\n';

}

/*
brainstorming:

[drew some pictures]

buy at the first minimum (because buying earlier is strictly worse)
sell at the next local maximum (because buying and selling multiple times is better than only once)

repeat
*/