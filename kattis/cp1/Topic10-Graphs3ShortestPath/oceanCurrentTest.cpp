

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

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795

typedef struct node_dist {
  int x;
  int y;
  int dist;
} nd;

bool compareND(const nd& lhs, const nd& rhs)
{
  return lhs.dist < rhs.dist;
}


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  priority_queue<nd, vector<nd>, compareND> pq;

  nd node = {1, 1, 5};

  pq.push(node);

  node.x = -5;
  node.dist = 10;

  pq.push(node);

  node.dist = -23948;
  node.y = -3;

  pq.push(node);

  while (!pq.empty()) {
    cout << pq.top().dist << endl;
    pq.pop();
  }


}

// this problem screams floyd warshall


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp