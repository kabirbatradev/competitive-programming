

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
  string prefix = "";
  while (true) {
    int n, m, q; cin >> n >> m >> q;
    if (n == 0 && m == 0 && q == 0) {
      break;
    }
    cout << prefix;
    prefix = "\n";

    // adjacency matrix
    int am[n][n];
    // first arg to second arg, stores weight

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        am[i][j] = INT_MAX;

    for (int mi = 0; mi < m; mi++) {
      int u, v, w; cin >> u >> v >> w;
      // I DIDNT CONSIDER MULTIPLE EDGES CONNECTING SAME NODES
      am[u][v] = min(w, am[u][v]);
    }

    // int dist[n][n] = am;
    for (int i = 0; i < n; i++) {
      am[i][i] = min(0, am[i][i]);
    }
    
    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++)
    //     cout << am[i][j] << " ";
    //   cout << "\n";
    // }

    for (int k = 0; k < n; k++) 
      for (int u = 0; u < n; u++) 
        for (int v = 0; v < n; v++) {
          if (am[u][k] == INT_MAX || am[k][v] == INT_MAX) continue;
          am[u][v] = min(am[u][v], am[u][k] + am[k][v]);
          // cout << min(am[u][v], am[u][k] + am[k][v]) << endl;
        }

    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++)
    //     cout << am[i][j] << " ";
    //   cout << "\n";
    // }

    vector<int> negativeCycles;
    for (int i = 0; i < n; i++) {
      if (am[i][i] != 0) negativeCycles.push_back(i);
    }

    for (int qi = 0; qi < q; qi++) {
      int u, v; cin >> u >> v;
      if (am[u][v] == INT_MAX) {
        cout << "Impossible" << "\n";
      }
      else {
        bool bad = false;
        for (int badNode : negativeCycles) {
          if (am[u][badNode] != INT_MAX && am[badNode][v] != INT_MAX) {
            cout << "-Infinity" << "\n";
            bad = true;
            break;
          }
        }

        if (!bad) {
          cout << am[u][v] << "\n";
        }
        
      }
      
    }

  }

}

// this question actually screams floyd warshall lol
// graph is directed
// need to detect infinite negative cycles

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp