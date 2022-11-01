

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

// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);


  ll sizes, colors;
  cin >> sizes >> colors;

  vector<ll> sizesList;
  sizesList.reserve(sizes);
  vector<ll> colorsList;
  colorsList.reserve(colors);


  for (ll i = 0; i < sizes; i++) {
    ll size;
    cin >> size;
    sizesList.push_back(size);
  }

  for (ll i = 0; i < colors; i++) {
    ll color;
    cin >> color;
    colorsList.push_back(color);
  }

  sort(sizesList.begin(), sizesList.end());
  sort(colorsList.begin(), colorsList.end());

  // read the first colorsList, iterate to the sizesList that is big enough
  // then go plus 1

  ll sizeIndex = 0;
  ll paintWasted = 0;

  for (ll i = 0; i < colorsList.size(); i++) {
    ll sizeNeeded = colorsList.at(i);
    while (true) {
      if (sizesList.at(sizeIndex) >= sizeNeeded) {
        paintWasted += sizesList.at(sizeIndex) - sizeNeeded;
        // sizeIndex++;
        break;
      }
      sizeIndex++;

    }
  }

  cout << paintWasted << endl;

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp