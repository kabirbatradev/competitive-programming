

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

int targetPrice;
vector<int> bestList; // empty if not initialized
int bestOvershoot;
int bestBillCount; // is just the bestList.size() lol

void tryNewCombination(vector<int> currentSequence, vector<int> remainingBills) {
  int sum = accumulate(currentSequence.begin(),currentSequence.end(),0);
  if (sum >= targetPrice) {
    // if nothing is initialized:
    int overshoot = sum - targetPrice;

    if (bestList.size() == 0) {
      bestList = currentSequence;
      bestOvershoot = overshoot;
      bestBillCount = currentSequence.size();
    }

    // if things are already initialized: 
    else {
      if (overshoot < bestOvershoot) {
        // we have a new winner
        bestList = currentSequence;
        bestOvershoot = overshoot;
        bestBillCount = currentSequence.size();
      }
      else if (overshoot == bestOvershoot) {
        if (currentSequence.size() < bestBillCount) {
          // we have a new winner by number of bills
          bestList = currentSequence;
          bestOvershoot = overshoot;
          bestBillCount = currentSequence.size();
        }
      }
    }
  }

  // if we have not overshot yet
  else {
    int previousBill = -1;
    for (int i = 0; i < remainingBills.size(); i++) {
      int newBill = remainingBills.at(i);

      // if not the first loop
      if (previousBill != -1) {
        if (newBill == previousBill) {
          continue;
          // we have already tried this combination, so might as well skip
        }
        // if they aren't the same, then update previous bill
        previousBill = newBill;
      }

      vector<int> currentSequenceCopy = currentSequence;
      currentSequenceCopy.push_back(newBill);

      vector<int> remainingBillsCopy = remainingBills;
      remainingBillsCopy.erase(remainingBillsCopy.begin() + i);

      tryNewCombination(currentSequenceCopy, remainingBillsCopy);

    }
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n;
  cin >> n;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  for (int i = 0; i < n; i++) {
    int price;
    cin >> price;
    targetPrice = price;

    int billCount;
    cin >> billCount;

    vector<int> bills;
    bills.reserve(billCount);

    for (int j = 0; j < billCount; j++) {
      int currentBill;
      cin >> currentBill;

      bills.push_back(currentBill);

    }

    sort(bills.begin(), bills.end(), std::greater<int>());
    // find optimal solution by searching through every combination
    vector<int> initialSequence;
    // initial sequence is blank, the remaining bills are all of them
    tryNewCombination(initialSequence, bills);

    cout << price + bestOvershoot << " " << bestBillCount << "\n";

    bestList.clear();
    // should reset the function for the next input

  }

}


// ideas?
// well we want least bills and we want minimum change
// without the last (smallest) bill given, say the problem is solved
// now the last bill is introduced
// add it
// if we have not reached goal price, then just keep going lol
// if we had already passed the goal price, then
  // we have to try to find the best possible combination, now with this new bill
  // let x = how much we overshoot
  // recursively go through the entire solution set, and mess with it while
  // keeping track of the best so far
  // delete smaller values first, keep deleting until we stopped overshooting,
    // the recursive alg does a for loop but breaks when we try to delete a 
    // value that is greater than the overshoot itself (assuming the solution
    // is sorted from least to greatest)
  // store the best combination of not overshooting

  // okay but what if the optimal solution involes a value that was not used in
  // the original solution?



// new idea
// what if we brute force
// simply iterate through every possibly combination of bills until you get one that
// overshoots the least and has the least combinations
// this is just recursion complete search kind of stuff but /shrug
// is it worth a shot until I can come up with a better idea? Sure!
  // make a function that takes in (currentSequence, remainingBills)
  // also global variables for
  // bestList, bestOvershoot, bestNumberOfBills
// the function:
  // iterates through the entire remainingBills
  // takes the currentSequence and adds a remainingBill
  // passes that to the function again
  // if it overshoots, then thats okay
  // if it has already overshoot, then compare with the global variables
    // dont call the function again if has already overshoot
  // if it still hasnt overshoot, just keep going?
  // if bestNumberOfBills has been passed, then we can stop this recursive run
  // also, if we run out of bills, we shouldve overshot the price anyway,
  // so basically dont need to worry that remaining bills is empty

// one thing i notice: we are taking the sum of groups of bills that maybe
// we have already taken the sum of
// imagine making one of those sum matricies
// that would be interesting but I dont see how it would be useful right now
// since the sums vary and can have missing elements in the set
// so we can't really predetermine sums


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
