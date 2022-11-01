

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
#include <climits>

using namespace std;
using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  
  int N, H, L; cin >> N >> H >> L;

  int horrorRatings[N];

  for (int i = 0; i < N; i++) {
    horrorRatings[i] = INT_MAX;
  }

  queue<int> bfsQueue;

  // horror list
  for (int hi = 0; hi < H; hi++) {
    int xi;
    cin >> xi;
    horrorRatings[xi] = 0;
    bfsQueue.push(xi);
  }

  vector<int> adjacencies[N];

  for (int li = 0; li < L; li++) {
    int ai, bi; cin >> ai >> bi;
    adjacencies[ai].push_back(bi);
    adjacencies[bi].push_back(ai);
  }

  while (!bfsQueue.empty()) {
    int current = bfsQueue.front();
    bfsQueue.pop();

    for (int id : adjacencies[current]) {
      if (horrorRatings[id] == INT_MAX) {
        horrorRatings[id] = horrorRatings[current] + 1;
        bfsQueue.push(id);
      }
    }

  }

  int max = 0;
  int bestIndex = 0;

  for (int i = 0; i < N; i++) {
    if (horrorRatings[i] > max) {
      max = horrorRatings[i];
      bestIndex = i;
    }
  }

  cout << bestIndex << "\n";
  
}

// i think if we do bfs 
// and then go thru the entire thing and find the smallest one

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp