

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

  int X; cin >> X;
  int counter = 0;

  int N = (int) ceil(sqrt(X));
  bool primes[N];
  // index 0 is 1
  for (int i = 0; i < N; i++) {
    if (i % 2 == 0) {
      primes[i] = true;
    }
  }

  int current_prime = 2;
  
  while (X != 1) {

    if (X % current_prime == 0) {
      X = X / current_prime;
      counter++;
      // cout << current_prime << endl;
      continue;
    }

    for (int i = current_prime-1; i < N; i += current_prime) {
      primes[i] = false;
    }

    int index = current_prime - 1;
    index++;
    if (index == N) {
      break;
    }
    while (!primes[index]) {
      index++;
      if (index == N) {
        break;
      }
    }
    if (index == N) {
      break;
    }
    current_prime = index + 1;
  }

  if (X != 1) {
    cout << counter + 1 << endl;
  }
  else {
    cout << counter << endl;
  }

  


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp