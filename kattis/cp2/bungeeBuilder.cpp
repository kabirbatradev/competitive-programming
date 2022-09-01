
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// const int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
// ll is kinda op pog use it ALWAYS
// #define PI 3.1415926535897932384626433832795

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // cout.precision(10);

  int n;  // number of mountains
  cin >> n;

  // index, height
  deque<pair<int, int> > tallest2Mountains;

  int count = 0;

  int shortestInThisWindow = -1;
  int bestAnswer = 0;

  for (int i = 0; i < n; i++) {
    int h;
    cin >> h;

    if (count == 0) {
      tallest2Mountains.push_back(make_pair(i, h));
      count++;
      continue;
    }
    
    // if the second mountain is shorter, then we add it, add count, and it is the shortest so far
    // if it is taller, then we restart the window from the second mountain (because we cannot build a bridge with something between)
    if (count == 1) {
      if (h < tallest2Mountains.back().second) {
        tallest2Mountains.push_back(make_pair(i, h));
        shortestInThisWindow = h;
        count++;
        continue;
      }
      // else (same height or taller should be treated the same)
      // restart window, reset shortest, count = 1
      tallest2Mountains.clear();
      tallest2Mountains.push_back(make_pair(i, h));
      shortestInThisWindow = -1;
      // count = 1; is alr 1
      continue;
    }

    // if new mountain is taller or same height as first, then we must do a final check and restart the window
    if (h >= tallest2Mountains.front().second) {
      int bridgeHeight = tallest2Mountains.front().second;
      if (shortestInThisWindow != -1) {
        int jumpHeight = bridgeHeight - shortestInThisWindow;
        if (jumpHeight > bestAnswer) bestAnswer = jumpHeight;
      }

      // restart the window/reset
      tallest2Mountains.clear();
      tallest2Mountains.push_back(make_pair(i, h));
      shortestInThisWindow = -1;
      count = 1;

      continue;

    }

    // if the new mountain is taller or same height as the second, then we do a check for possible answer and replace the second with the new mountain
    // we do a check for the same height again because the shortest in this window might have become shorter
    if (h >= tallest2Mountains.back().second) {
      // if h was the taller moutanin, then the code above would have run
      int bridgeHeight = h;
      if (shortestInThisWindow != -1) {
        int jumpHeight = bridgeHeight - shortestInThisWindow;
        if (jumpHeight > bestAnswer) bestAnswer = jumpHeight;
      }

      tallest2Mountains.back().first = i;
      tallest2Mountains.back().second = h;

      continue;
    }

    // if neither, then we see if this is the shortest so far and continue
    if (shortestInThisWindow == -1 || h < shortestInThisWindow) {
      shortestInThisWindow = h;
    }
    


  }

  cout << bestAnswer << endl;

}

// seems like we can use something related to a monotonic stack
// honestly not really?

// in order to solve this problem, we need to find 2 of the tallest mountains in the window, 
// the shortest mountain in the window, and then consider the height difference between the shortest and the second tallest
// the window width is defined by the 2 tallest mountains, so

// we should store a tallest and second tallest since they define the window
// if the tallest came first, we can keep growing the window
// if the tallest comes later, then that is the end of the window, 
  // so do a final check for if we have a new best
  // and a new window begins
// if we get a tall mountain and we keep getting shorter, then our second tallest's
// position defines where we can look for shorter mountains...

// so we should always keep track of the shortest in the window so far
// and whenever we get a new second tallest, we can do a calculation for the best answer so far (best height difference)
// and also if we get a new first tallest, we do a check and also restart the window from there
// if the 2 tallest mountains are the same height, just treat the new one as taller and restart the window

// and yeah thats it!