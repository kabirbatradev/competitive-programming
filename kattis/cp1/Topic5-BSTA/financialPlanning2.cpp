

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


struct investment {
  ll dailyProfit;
  ll initialCost;
  ll profitAfterXDays;
};


// comparison function for the structure to be used by sort
bool compareByTotalProfit(const investment &a, const investment &b)
{
  return a.profitAfterXDays > b.profitAfterXDays;
}


bool isPossible(ll M, ll givenDays, vector<struct investment> investmentList) {

  // set profitAfterXDays for everything in the vector
  for (int i = 0; i < investmentList.size(); i++) {
    struct investment currentInv = investmentList.at(i);
    investmentList.at(i).profitAfterXDays = currentInv.dailyProfit * givenDays - currentInv.initialCost;
  }

  sort(investmentList.begin(), investmentList.end(), compareByTotalProfit);

  ll total = 0;

  for (int i = 0; i < investmentList.size(); i++) {
    struct investment currentInv = investmentList.at(i);
    // investmentList.at(i).profitAfterXDays = currentInv.dailyProfit * givenDays - currentInv.initialCost;


    // cout << currentInv.profitAfterXDays << endl;
    // cout << total << endl;

    if (currentInv.profitAfterXDays > 0) {
      total += currentInv.profitAfterXDays;
      if (total >= M) {
        return true;
      }
    }
    else { // reached negative profit but still haven not exceeded M
      return false;
    }

  }

  return false;
  
}



int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  

  int n, M;
  cin >> n >> M; // m is the total amount profit - initial cost i want

  vector<struct investment> investmentList;
  investmentList.reserve(n);

  for (int i = 0; i < n; i++) {
    int pi, ci; // daily profit, initial cost
    cin >> pi >> ci;
    struct investment newInvestment = {pi, ci, 0};

    investmentList.push_back(newInvestment);
  }


  // we BSTA (answer is min days)
  ll min = 1;
  ll max = (int)1e9 + 1;

  ll middleIndex;

  ll bestAnswerSoFar = max;

  while (true) {

    if (min >= max) {

      

      
      if (min < bestAnswerSoFar) {
        if (isPossible(M, min, investmentList)) {
          bestAnswerSoFar = min;
        }
      }

      if (isPossible(M, bestAnswerSoFar-1, investmentList)) {
        cout << bestAnswerSoFar-1 << endl;
        break;
      }
      if (isPossible(M, bestAnswerSoFar, investmentList)) {
        cout << bestAnswerSoFar << endl;
        break;
      }
      if (isPossible(M, bestAnswerSoFar+1, investmentList)) {
        cout << bestAnswerSoFar+1 << endl;
        break;
      }

      // print the answer!
      // cout << min << endl;
      break;
    }

    middleIndex = (max + min) / 2; // rounded down!

    if (isPossible(M, middleIndex, investmentList)) {
      // this number of days is possible, so lets try lower
      bestAnswerSoFar = middleIndex;

      max = middleIndex;
      // although we already considered this index, it might be the final answer
      // so we dont want to get rid of it 
      // originally did max = middleIndex - 1 (mistake)

    }
    else {
      // not possible, so we have to try higher

      min = middleIndex + 1;
      // + 1 because we have already tried middle


    }


  }

  // cout << isPossible(M, 10, investmentList) << endl;
  


}


// the answer space is "minimum days" which is monotonic
// our goal is to minimize this answer space while seeing if its possible or not

// step 1: make a function that tells us if a certain "minimum days" input is possible
// step 2: try a bunch of values for minimum days till we get it


// how to do step 1:

// if they say: "1 day"
// we sort every investment by profit after 1 day
// ex: 4, 10: profit = -10 + 4 * (1 day) = -6 
// we sort these by greatest first, and we take all the positive ones and see if
// that is greater than M

// if they say: "2 days"
// we sort every investment by profit after 2 days
// ex: 4, 10: profit = -10 + 4 * (2 day) = -2 
// we sort these by greatest first, and we take all the positive ones and see if
// that is greater than M


// how to do step 2:

// we need a best case: 1
// we need a worst case: 10^9 + 1
//     because: profit = 1, initial cost = 10^9, number of days = 10^9 + 1

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp