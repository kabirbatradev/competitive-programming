

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

  while (true) {
    int n; cin >> n;

    if (n == 0) {
      break;
    }

    int arr[501][501] = {0};

    for (int i = 0; i < n; i++) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;

      for (int x = a; x < c; x++) {
        for (int y = b; y < d; y++) {
          arr[x][y] = 1;
        }
      }
      
    }

    int counter = 0;
    for (int x = 0; x < 501; x++) {
    for (int y = 0; y < 501; y++) {
      if (arr[x][y] == 1) {
        counter++;
      }
    }
    }

    cout << counter << "\n";

  }
  

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp