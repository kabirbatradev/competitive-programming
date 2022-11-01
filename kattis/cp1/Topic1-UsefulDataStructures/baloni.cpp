

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

// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int totalArrows = 0;
  vector<int> arrowsHeight;

  int balloons;
  cin >> balloons;
  for (int xPos = 0; xPos < balloons; xPos++) {
    
    int balloonHeight;
    cin >> balloonHeight;

    int arrowIndex = -1;
    for (int i = 0; i < arrowsHeight.size(); i++) {
      if (arrowsHeight.at(i) == balloonHeight) {
        arrowIndex = i;
        break;
      }
    }

    if (arrowIndex != -1) {
      arrowsHeight.at(arrowIndex)--;
    } else {
      arrowsHeight.push_back(balloonHeight - 1);
      totalArrows += 1;
    }
      
  }

  cout << totalArrows << endl;

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp