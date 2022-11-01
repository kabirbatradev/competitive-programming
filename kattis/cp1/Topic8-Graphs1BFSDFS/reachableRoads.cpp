

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


// struct pairasohig {
//   int x;
//   int y;
// };

int main() {


  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int n;
  cin >> n;

  // vector<struct pair> nums;'aef';dhboaegilsdhb [orsih[]]

  for (int tc = 0; tc < n; tc++) {
    // vector<struct pairasohig> pairs;

    int m; cin >> m;
    int remainingRoads = m;

    // make parents array
    int parents[m];
    int rank[m];

    for (int i = 0; i < m; i++) {
      // asdfasdfaedfw;efjwjkoewkofjk
      parents[i] = i;
      rank[i] = 1;
    }

    int r; cin >> r;
    for (int i = 0; i < r; i++) {
      // struct pairasohig temp = {};
      // cin >> temp.x >> temp.y;
      // // pairs.push_back(temp);

      // tempsajdkfhalidgskaldf

      int x, y;
      cin >> x >> y;
      // okay now lets update the parents array

      // if (rank[x] >= rank[y]) {
      //   // x is the superior parent
      //   parent
      // }
      // else {

      // }

      // we want rank of the parent of x and parent of y
      int parentX = parents[x];
      int parentY = parents[y];
      if (parentX == parentY) {
        // dONT don
        // DONT INCREASE ANYTIHNG
        // so this pair is pointless and we can
        continue;
      }
      if (rank[parentX] >= rank[parentY]) {
        // xParent is the superior parent
        // we should increase the rank of x's parent
        // by the rank of y's parent
        // and also replace all times where 
        // there is a node that has a parent that is the same as parentY
        // i wnat t odfuiasdgasdid e

        rank[parentX] += rank[parentY];
        // iterate through all parents and if any of them are parentY, then set them to parentX
        for (int j = 0; j < m; j++) {
          if(parents[j] == parentY) {
            parents[j] = parentX;
          }
        }
        remainingRoads--;

      }
      else {

        // everything same but switch x and y
        int temp = x;
        x = y;
        y = temp;

        temp = parentX;
        parentX = parentY;
        parentY = temp;

        rank[parentX] += rank[parentY];
        // iterate through all parents and if any of them are parentY, then set them to parentX
        for (int j = 0; j < m; j++) {
          if(parents[j] == parentY) {
            parents[j] = parentX;
          }
        }
        remainingRoads--;


      }

      // so 2 nodes have a parent node that is the same node
      // means they are connected
      // lets say 123 are connectd, 456 are connected
      // then 3 4 connect, but 4 already has a parent that is not 4 (possibly)
      // and other numbers already have parents that are the same parent as 4
      // now we want 4's parents to be the same as 3's parents
      // which means that all the nodes that have the same parent as 4 should also be changed
      // okay but also do we even care?
      // we keep decreasing the count unless 3 and 4 have the same parent, right?
      // but then lets say we get 3 6
      // they are already connected by 3 4, so they should have the same parent
      // but they dont because of the previous problem
      // so we do care about this problem
      // and the solution is to iterate through the entire array whenever this happens and 
      // go through all the elements that have the same parent as 4 and then set them to the new superior parent
      // the parent that is superior is determined by the parent's rank
      // so if a parent has 1 child, its rank is 1, and if it has 4, then its rank is 4



      // parents[m]
      // remainingRoads--;


    }

    // okay so now we know roads
    // exist from 0 to m - 1
    // and we know that we have certain road connections
    // lets find all the complete graphs
    // this means we only need as many roads as there are complete graphs
    // so make a complete graph counter
    // they are ccalled fd compeondigosekjgdfiluhgkablskd.fjgvilszkdjgcm.vslijerkd.gfh,cv
    // they are called connected components

    cout << remainingRoads-1 << "\n";
    



  }
  


}

// i have no idea what to do
// this is bfs right?
// wth is bfs idaidfaowebgisdfgs

//help



// so we have pairs lol

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp