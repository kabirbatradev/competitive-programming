#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {

    int t; cin >> t;

    // number, followed by original order index
    vector<pair<int, int>> nums(t);
    for (int i = 0; i < t; i++) {
      int n; cin >> n;

      nums[i] = {n, i};
    }

    sort(nums.begin(), nums.end()); // sorted by value, smallest first

    vector<int> answers(t);

    int x = 45; // first num that has a difference when rounded

    int multiplier = 100;
    int i = 0; // index in nums
    int offsetToPeak = 4;
    // while there are still nums left (test cases) to process
    int counter = 0;
    while (i < t) {

      int N = nums[i].first;
      int answerIndex = nums[i].second;

      if (x <= N) {
        // this N still has more to count
        // int offsetToPeak = x / 10;
        int peak = x + offsetToPeak;
        // if N is less than peak, then this N doesnt get the whole range, and this num is done
        if (N < peak) {
          answers[answerIndex] = counter + (N - x + 1); // save answer
          i++; // move on to next N
          continue;
        }
        // but if N is equal to peak or more, then add the full thing, update x and offset, and restart
        else {
          counter += (peak - x + 1); // add the full thing
          x += 4*multiplier; // x is now 445 from 45
          offsetToPeak += 5 * (multiplier/10); // now 54 from 4
          multiplier *= 10; // update multipler
          continue;
        }
      }
      else {
        // this N is done
        answers[answerIndex] = counter; // save answer
        i++; // move on to next N
        continue;
      }

    }

    // print all test case answers in order
    for (int num : answers) {
      cout << num << '\n';
    }


  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
Bessie rounds based on one digit
rest is 0s
note: if num is 95, then we round up, and 9 overflows 
  so we need to add one to the next digit, which might not exist, so add an extra 0 to the left

elsie rounds all of the earlier numbers first
if the rounding number is already 5 or more, or 3 or less, it doesnt make any difference
but if the rounding number is 4, then it could be pushed to a 5 
  the previous number needs to be a 5 or higher
  or it needs to be a 4 and the previous previous needs to be 5+

question: how many integers between 2 and N (given) exist such that rounding is different from chain rounding
  we around at 10^P
  where 10^P >= num but P is minimized
  so if x = 11 through 100, then 10^P is 100
    P is 2, so we round the 2nd digit from the right
  its basically like rounding the leftmost digit unless we have a multiple of 10

they are always the same unless:
  leftmost digit is a 4
  here, elsie might round up
how do we count the number of cases where this happens?
  4 fails
  45 is the first difference
  45 through 49 = 5 nums
  then 445 through 499 = 5 + 50 nums
  then 4445 through 4999 = 5 + 50 + 500 nums
  ...
  until the number is equal to N

sudo code:
  x = 45
  repeat:
    if x <= N, 
      add to counter x through to its peak, or N itself, whichever is first
      add a 4 to the left of x
    otherwise, break
  print counter

  whats a quick way to get "peak" for some particular x?
    x can only be 45, 445, 4445, ...
    peak can only be 49, 499, 4999
    note that the offset is 5-1, 55-1, 555-1, ...

can we make this efficient for multiple test cases?
  sort the test cases, process them in order
  continue where the previous test case left off
  then print the results in the correct order (store values in already correct order array)
*/