

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

typedef struct sumAndIndex {
  ll sum;
  int index;
} sum;

bool compareSum(sum &s1, sum &s2) {
  return s1.sum < s2.sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  

  int t;
  cin >> t;

  // int N = (int)1e5;
  // vector<int> nums;
  // nums.reserve(N);

  for (int tc = 0; tc < t; tc++) {
    string blank;
    getline(cin, blank);

    int n;
    cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    vector<sumAndIndex> sums;

    ll sumSoFar = 0;
    for (int i = 0; i < n; i++) {
      sumSoFar += nums[i];
      sum temp = {sumSoFar, i};
      sums.push_back(temp);
    }

    sort(sums.begin(), sums.end(), compareSum);

    int p1 = 0, p2 = 0;
    int counter = 0;

    // check all the elements by themselves
    for (int i = 0; i < n; i++) {
      sum s = sums.at(i);
      if (s.sum == 47) {
        counter++;
      }
    }

    // two pointer approach gives the wrong answer for the last
    // test case

    while (p1 < n && p2 < n) {

      ll ssum = 0;
      sum p1sum = sums.at(p1);
      sum p2sum = sums.at(p2);

      ssum = p2sum.sum - p1sum.sum;

      if (ssum == 47) {
        if (p2sum.index > p1sum.index) {
          counter++;
        }

        // i say we check all possibilities with making a sum
        // using the second pointer in the same position,
        // and then we eventually increment the second pointer
        // and set the first pointer back
        int oldP1 = p1;
        while (true) {
          p1++;
          p1sum = sums.at(p1);
          if (p1 == p2) {
            break;
          }
          ssum = p2sum.sum - p1sum.sum;
          if (ssum == 47) {
            if (p2sum.index > p1sum.index)
            counter++;
          }
          // otherwise the sum has gotten too small and we need to increase p2
          // so we can go back to the original loop
          // it is impossible for the sum to get larger
          // since the sums are sorted and we are only increasing
          // the first pointer.
          else {
            break;
          }
        }
        p1 = oldP1;
        p2++;
      }
      else if (ssum > 47) {
        p1++;
      }
      else if (ssum < 47) {
        p2++;
      }
    }

    cout << counter << "\n";



  }

}

// lets create a 1d prefix sum
// sort it but also store its original position
// then do the pointers approach, but only increment the counter
// if the second pointer's original pos > first og pos

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp