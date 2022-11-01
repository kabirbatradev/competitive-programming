

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

  int r, c;
  cin >> r >> c;

  int map[r][c];

  for (int i = 0; i < r; i++) {

    string line;
    cin >> line;
    for (int j = 0; j < c; j++) {
      map[i][j] = line[j] - '0';
    }

  }

  int next1Label = 2;
  int next0Label = -1;

  int n;
  cin >> n;

  for (int tc = 0; tc < n; tc++) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;

    if (map[r1][c1] != map[r2][c2]) {
      cout << "neither\n";
      continue;
    }
    if (r1 == r2 && c1 == c2) {
      cout << (map[r1][c1] > 0 ? "decimal\n" : "binary\n");
      continue;
    }
    if (map[r1][c1] != 0 && map[r1][c1] != 1) {
      // if (map[r1][c1] == map[r2][c2]) {
        cout << (map[r1][c1] > 0 ? "decimal\n" : "binary\n");
        continue;
      // }
      // else {
      //   cout << "neither\n";
      //   continue;
      // }
    }

    bool visited[r][c];
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        visited[i][j] = false;
      }
    }

    list<pair<int, int> > queue;
    pair<int, int> p1 (r1, c1);
    queue.push_back(p1);

    int type = map[r1][c1];
    bool found = false;

    while (!queue.empty()) {
      pair<int, int> current = queue.front();
      queue.pop_front();


      if (visited[current.first][current.second]) {
        continue;
      }
      if (map[current.first][current.second] != type) {
        // includes if it has already been flood fill with another thign
        continue;
      }

      visited[current.first][current.second] = true;
      map[current.first][current.second] = (type ? next1Label : next0Label);

      if (current.first == r2 && current.second == c2) {
        found = true;
        // break;
        // search out the entire thing so we can fill it with all the correct numbers
      }

      for (int i = 0; i < 4; i++) {
        int x = current.first + dx[i];
        int y = current.second + dy[i];

        if (0 <= x && x < r && 0 <= y && y < c) {

          pair<int, int> newPair (x, y);

          queue.push_back(newPair);
        }
      }
    } /* end while */

    if (type == 0) {
      next0Label--;
    }
    else {
      next1Label++;
    }

    // for (int i = 0; i < r; i++) {
    //   for (int j = 0; j < c; j++) {
    //     cout << map[i][j];
    //   }
    //   cout << endl;
    // }
    // cout << endl;

    if (found) {
      cout << (type > 0 ? "decimal\n" : "binary\n");
    }
    else {
      cout << "neither\n";
    }
  }

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp