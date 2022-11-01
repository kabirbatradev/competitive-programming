

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

  int n, m, c;
  cin >> n >> m >> c;

  // int N = (int)1e5;
  vector<int> samples;
  samples.reserve(n);

  for (int i = 0; i < n; i++) {
    int samp;
    cin >> samp;
    samples.push_back(samp);
  }

  // if the counter is still 0 by the end, print NONE
  int counter = 0;

  // multiset<int> minHeap;
  // multiset<int> maxHeap;
  multiset<int> doubleHeap;

  // set up the heap for the first iteration
  for (int i = 0; i < m - 1; i++) {
    doubleHeap.insert(samples.at(i));
  }

  for (int i = 0; ; i++) {
    if (i + m - 1 == samples.size()) {
      break;
    }

    // add the i + m - 1 element 
    doubleHeap.insert(samples.at(i + m - 1));
    // remove the i - 1 element (if i != 0)
    if (i != 0) {
      doubleHeap.erase(doubleHeap.find(samples.at(i-1)));
    }

    // get min and max and check if <= c
    // if it is, print out i
    int min = *doubleHeap.begin();
    int max = *--doubleHeap.end();

    if (max - min <= c) {
      cout << i+1 << "\n";
      counter++;
    }
  }
  

  if (counter == 0) {
    cout << "NONE" << endl;
  }


}

// sliding window of size m - 1
// starting at some position i
// we keep track of the max and the min
// perhaps in the form of priority queues
// if the difference is smaller than c, then increase the counter
// and shift the sliding window 1 over
// and adjust the sliding window's min and max heap by getting rid of
// the element that was lost, and inserting the new element that was added

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp