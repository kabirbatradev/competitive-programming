

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;
using ll = long long;

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n;
  cin >> n;

  for (int t = 0; t < n; t++) {
    int price;
    cin >> price;


    int billCount;
    cin >> billCount;
    vector<int> bills;
    bills.reserve(billCount);
    for (int j = 0; j < billCount; j++) {
      int currentBill;
      cin >> currentBill;
      bills.push_back(currentBill);
    }

    // sort(bills.begin(), bills.end(), std::greater<int>());
    sort(bills.begin(), bills.end(), std::greater<int>());

    // dp[i][j], i = coin index, j = price
    int dp[billCount + 1][20000 + 1]; // 10000 is the max cost

    // set everything to max
    for (int i = 0; i < billCount + 1; i++) {
      for (int j = 0; j < 20000 + 1; j++) {
        dp[i][j] = INT_MAX;
      }
    }

    // set the price = 0 column to 0 coins
    for (int i = 0; i < billCount + 1; i++) {
      dp[i][0] = 0;
    }
    // for (int j = 0; j < 20000 + 1; j++) {
    //   dp[0][j] = max;
    // }

    for (int i = 1; i < billCount + 1; i++) {
      for (int j = 1; j < 20001; j++) {
        int min = dp[i][j];

        if (i-1 >= 0) {
          if (dp[i-1][j] < min) {
            min = dp[i-1][j];
          }
        }
        if (j - bills.at(i-1) >= 0) {
          if (dp[i][j - bills.at(i-1)] != INT_MAX && dp[i][j - bills.at(i-1)] + 1 < min) {
            min = dp[i][j - bills.at(i-1)] + 1;
          }
        }
        dp[i][j] = min;
      }
    }

    // for (int i = 0; i < billCount + 1; i++) {
    //   for (int j = 0; j < 5; j++) {
    //     cout << dp[i][j] << "\t";
    //   }
    //   cout << endl;
    // }


    // print the answer
    // get dp at price 
    // given all coins!

    // if j is price and we have not infinity, then that is answer
    for (int j = price; j < 20001; j++) {
      if (dp[billCount][j] != INT_MAX) {
        // cout << "price: " << j << " number of coins: " << dp[billCount][j] << endl;
        cout << j << " " << dp[billCount][j] << endl;
        break;
      }
    }

    // for (int i = 0; i < billCount + 1; i++) {
    //   if (dp[i][price] != INT_MAX) {
        
    //   }
    // }

  }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp