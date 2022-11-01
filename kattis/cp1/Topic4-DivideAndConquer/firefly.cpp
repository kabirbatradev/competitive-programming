

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

  int groundIndex = fromGround.size() - 1;
  int roofIndex = 0;
  for (int i = 0; i < H; i++) {
    while (true) {
      if (groundIndex == 0) {
        break;
      }
      if (i <= fromGround.at(groundIndex)) {
        break;
      }
      groundIndex--;
    }

    while (true) {
      if (roofIndex >= fromRoof.size()) {
        break;
      }
      if (i >= H - fromRoof.at(roofIndex)) {
        break;
      }
      roofIndex++;
    }

    int walls = groundIndex + roofIndex - 1;
    
    

    
  }

  // should we just iterate through every height?
  // then we would start at 0, and we would start at the end of
  // forGround to see if that end node was taller than 0
  // if its not taller than the index, then move it and check the next
  // from the back of forGround until we find one that is larger than 
  // the height we are checking. Then, the current index(from the start)
  // we just reached is the number of nodes that are long enough from
  // the bottom to reach that height.
  
  // then, we start at the fromRoof except we do height - node
  // and check if that is smaller than 0, because if that is smaller,
  // then we have something so long that it reaches the current height
  // if its tall enough, then we keep increasing until we find one that
  // is not long enough to reach the current height from the roof,
  // and our current index-1 is the number of ones fromRoof that reach.

  // once we have both these numbers, them summed gets us the count for that height
  // no we repeat this process, but we increase the height, and we start from
  // the same index, but move in the direction that will give us an accurate count
  // for a larger height

  // we will keep going since the total gets smaller
  // once the total gets bigger, then that means that its only getting bigger from here
  // says my intuition..

}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp