

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

const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n, m; cin >> n >> m;

  int nodeDegree[n]; // number of above
  int output[n];
  for (int i = 0; i < n; i++) {
    nodeDegree[i] = 0;
    output[i] = 0;
  }
  vector<int> nodeisAbove[n];

  for (int tc = 0; tc < m; tc++) {
    pair<int, int> stick;
    cin >> stick.first >> stick.second;
    stick.first--;
    stick.second--;

    // first is above second
    nodeDegree[stick.second]++;
    nodeisAbove[stick.first].push_back(stick.second);
  }

  list<int> queueOfRemovingSticks;

  for (int i = 0; i < n; i++) {
    if (nodeDegree[i] == 0) {
      queueOfRemovingSticks.push_back(i);
    }
  }

  int index = 0;

  while (!queueOfRemovingSticks.empty()) {
    int nodeRemove = queueOfRemovingSticks.front();
    queueOfRemovingSticks.pop_front();

    // cout << nodeRemove + 1 << "\n";
    output[index] = nodeRemove + 1;
    index++;

    for (int i : nodeisAbove[nodeRemove]) {
      // for every node above, decrement counter and if its 0 then remove it
      nodeDegree[i]--;
      if (nodeDegree[i] == 0) {
        queueOfRemovingSticks.push_back(i);
      }
    }
  }

  if (index != n) {
    cout << "IMPOSSIBLE\n";
  }
  else {
    for (int i = 0; i < n; i++) {
      cout << output[i] << "\n";
    }
  }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp