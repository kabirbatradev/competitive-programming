

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

typedef struct node_dist {
  int row;
  int col;
  int dist;
} nd;

struct compareND {
  bool operator() (const nd& lhs, const nd& rhs)
  {
    return lhs.dist > rhs.dist;
  }
};

int conversion[] = {7, 0, 1, 6, -1, 2, 5, 4, 3};


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int r, c; cin >> r >> c;
  int dirGrid[r][c];
  for (int ri = 0; ri < r; ri++) {
    string row; cin >> row;

    for (int ci = 0; ci < c; ci++) {
      dirGrid[ri][ci] = row[ci] - '0';
    }

  }

  int n; cin >> n;
  for (int ni = 0; ni < n; ni++) {
    int rs, cs, rd, cd; cin >> rs >> cs >> rd >> cd;
    rs--; cs--; rd--; cd--;

    bool visited[r][c];
    for (int ri = 0; ri < r; ri++) {
      for (int ci = 0; ci < c; ci++) {
        visited[ri][ci] = false;
      }
    }

    // pq of a struct that stores coord and distance
    priority_queue<nd, vector<nd>, compareND> pq;
    // start with the end, okay but why th lol im dumb
    nd last = {rd, cd, 0};
    pq.push(last);


    while (!pq.empty()) {
      nd current = pq.top();
      pq.pop();

      if (visited[current.row][current.col]) {
        continue;
      }


      cout << "reading " << current.row << " " << current.col << " " << current.dist << endl;


      // if this is the end, then print distance and end
      if (current.row == rs && current.col == cs) {
        cout << current.dist << "\n";
        break;
      }

      // add to queue all 8 directions, ignore direction if visited
      for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
          if (dr == 0 && dc == 0) continue;
          if (current.row + dr < 0 || current.row + dr >= r) continue;
          if (current.col + dc < 0 || current.col + dc >= c) continue;
          if (!visited[current.row + dr][current.col + dc]) {
            int temp = (dc + 1) + (dr + 1) * 3;
            // temp 0 - 8
            bool optimal = dirGrid[current.row][current.col] == conversion[temp];
            cout << dirGrid[current.row][current.col] << " " << conversion[temp] << endl;
            int newDistance = current.dist + (optimal ? 0 : 1);
            nd newPos = {current.row + dr, current.col + dc, newDistance};
            pq.push(newPos);
            cout << "adding " << newPos.row << " " << newPos.col << " " << newDistance << endl;
          }
        }
      }

      // mark this position as visited
      visited[current.row][current.col] = true;
    }

  }

}

// this problem screams floyd warshall
// but its too slow so lets do 50 dijkstras lol


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp