

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

  int N, H;
  cin >> N >> H;

  vector<int> fromGround;
  vector<int> fromRoof;
  fromGround.reserve(N/2);
  fromRoof.reserve(N/2);
  for (int i = 0; i < N; i++) {
    int size;
    cin >> size;
    fromGround.push_back(size);
    i++;
    cin >> size;
    fromRoof.push_back(size);
  }

  sort(fromGround.begin(), fromGround.end(), greater<int>());
  sort(fromRoof.begin(), fromRoof.end(), greater<int>());


  // for (int i : fromGround) {
  //   cout << "ground: " << i << endl;

  // }
  // cout << "\n";
  // for (int i : fromRoof) {
  //   cout << "roof: " << i << endl;
  // }

  // cout << "total height: " << H << endl;

  int numberOfFromGroundThatWeCrashInto = fromGround.size();
  int numberOfFromRoofThatWeCrashInto = 0;
  // cout << endl;

  int bestSoFar = N;
  int countOfBest = 0;

  for (int currentHeight = 1; currentHeight <= H; currentHeight++) {

    // caluculate how many from the ground
    while (true) {
      if (numberOfFromGroundThatWeCrashInto == 0) {
        break;
      }
      
      // this is the height of the last element (shortest)
      // if this height is less than the currentHeight
      // then, we should move the index over to the second shortest
      // and then the third shortest...
      // until we reach a thing that is equal to or greater than
      // the current height
      if (fromGround.at(numberOfFromGroundThatWeCrashInto - 1) < currentHeight) {
        numberOfFromGroundThatWeCrashInto--;
      }
      else break;
    }

    // cout << "fromGround: " << numberOfFromGroundThatWeCrashInto << endl;

    while (true) {
      if (numberOfFromRoofThatWeCrashInto == fromRoof.size()) {
        break;
      }
      
      // this is the height of the last element (shortest)
      // if this height is less than the currentHeight
      // then, we should move the index over to the second shortest
      // and then the third shortest...
      // until we reach a thing that is equal to or greater than
      // the current height
      if (H - fromRoof.at(numberOfFromRoofThatWeCrashInto) < currentHeight) {
        numberOfFromRoofThatWeCrashInto++;
      }
      else break;
    }

    // cout << "fromRoof: " << numberOfFromRoofThatWeCrashInto << endl;
    // cout << endl;

    int total = numberOfFromRoofThatWeCrashInto + numberOfFromGroundThatWeCrashInto;
    if (total < bestSoFar) {
      bestSoFar = total;
      countOfBest = 1;
    }
    else if (total == bestSoFar) {
      countOfBest++;
    }
  }

  cout << bestSoFar << " " << countOfBest << endl;


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp