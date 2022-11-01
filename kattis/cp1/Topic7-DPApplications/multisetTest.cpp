

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


int main() {

  multiset<int> ms;

  ms.insert(1);
  ms.insert(234);
  ms.insert(3);
  ms.insert(2);

  ms.insert(1);
  ms.insert(1);
  ms.insert(1);

  multiset<int>::iterator it;
  for (it = ms.begin(); it != ms.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  cout << ms.count(1) << endl;
  cout << *--ms.end() << endl;

  // ms.erase(1);
  ms.erase(ms.find(1));

  for (it = ms.begin(); it != ms.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;


  
}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp