

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




bool canFixWeights(vector<int> row1, vector<int> row2, int maxWeight) {
  // int i = 0;
  // while (i < row1.size()) {
  //   if (row1.at(i) <= maxWeight) {
  //     row1.erase(row1.begin() + i);
  //   }
  //   else {
  //     i++;
  //   }
  // }

  // i = 0;
  // while (i < row2.size()) {
  //   if (row2.at(i) <= maxWeight) {
  //     row2.erase(row2.begin() + i);
  //   }
  //   else {
  //     i++;
  //   }
  // }

  int current = -1;
  for (int i = 0; i < row1.size(); i++) {
    // cout << row1.at(i) << " ";


    // INSTEAD OF DELETING, I CAN JUST SKIP
    if (row1.at(i) <= maxWeight) {
      continue;
    }
    
    if (current == -1) {
      current = row1.at(i);
    }
    else {
      if (current == row1.at(i)) {
        current = -1;
      }
      else {
        return false;
      }
    }
  }
  // cout << endl;

  // forgot to check if the final pair was complete
  if (current != -1) {
    return false;
  }


  current = -1;
  for (int i = 0; i < row2.size(); i++) {
    // cout << row2.at(i) << " ";

    if (row2.at(i) <= maxWeight) {
      continue;
    }
    
    if (current == -1) {
      current = row2.at(i);
    }
    else {
      if (current == row2.at(i)) {
        current = -1;
      }
      else {
        return false;
      }
    }
  }
  // cout << endl;

  // check if final pair is complete
  if (current != -1) {
    return false;
  }


  return true;

}




int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  

  int n;
  cin >> n;

  vector<int> row1;
  vector<int> row2;
  row1.reserve(n);
  row2.reserve(n);

  int maxWeight = 0;

  for (int i = 0; i < n; i++) {
    int wi;
    cin >> wi;

    if (wi > maxWeight) {
      maxWeight = wi;
    }

    row1.push_back(wi);
  }

  for (int i = 0; i < n; i++) {
    int wi;
    cin >> wi;

    if (wi > maxWeight) {
      maxWeight = wi;
    }

    row2.push_back(wi);
  }


  // BSTA
  
  ll min = 0;
  ll max = maxWeight;

  ll middleIndex;

  while (true) {

    if (min >= max) {
      
      // print the answer!
      cout << min << endl;

      // if (min == 0) {
      //   cout << min << endl;
      //   break;
      // }


      // if (canFixWeights(row1, row2, min-1)) {
      //   // cout << "min - 1 worked" << endl;
      //   cout << min - 1 << endl;
      //   break;
      // }
      // if (canFixWeights(row1, row2, min)) {
      //   // cout << "min worked" << endl;
      //   cout << min << endl;
      //   break;
      // }
      // if (canFixWeights(row1, row2, min+1)) {
      //   // cout << "min + 1 worked" << endl;
      //   cout << min + 1 << endl;
      //   break;
      // }


      break;
    }

    middleIndex = (max + min) / 2; // rounded down!

    if (canFixWeights(row1, row2, middleIndex)) {
      // this number of days is possible, so lets try lower
      max = middleIndex;

    }
    else {
      // not possible, so we have to try higher

      min = middleIndex + 1;
      // + 1 because we have already tried middle


    }


  }

  // cout << canFixWeights(row1, row2, 2) << endl;


}


// if we wanted to binary search the answer here:
// step 1: create a functon that tells us if it is possible with the max weight being x
// step 2: BSTA from min = 0 to max = the max weight that shows up

// how to do step1:
// we know we are free to move any weight under the size of x
// so that means we can image that any weight under size x does not exist
// (because we moved it extremely far away so its like its not there)
// can we just roll around the remaining weights?
// aka are all of the remaining weights already in pairs? (easy to implement)

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp