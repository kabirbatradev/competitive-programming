#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {

    int n, l, w; 
    while (cin >> n >> l >> w) {

      // idea: convert circles into intervals that cover the full width
      vector<pair<double,double>> intervals;
      for (int i = 0; i < n; i++) {
        int x, r; cin >> x >> r;

        if (r*2 <= w) continue; // this circle is useless

        // hypotenuse = r
        // width of triangle = w / 2
        // len of triangle = ?
        double len = sqrt(r*r - (w/2.)*(w/2.));
        intervals.push_back(make_pair(x - len, x + len));

      }

      // go through intervals and dont turn on the ones that are overshadowed by others:
      // compare all the intervals that start before the last one ended.
        // pick the one that ends the latest
      
      sort(intervals.begin(), intervals.end()); // sorting by start
      int count = 0;
      double lastEndPoint = 0;
      int i = 0;

      while (true) {
        double largestNewEnd = -1;

        // go through all intervals that start before the last end point
        for (; i < intervals.size(); i++) {
          auto [start, end] = intervals[i];
          // start before last end point: check if this interval ends the latest and should be chosen
          if (start <= lastEndPoint) {
            largestNewEnd = max(largestNewEnd, end);
          }
          else {
            break; // maintains current "i" position for next iteration of while loop
          }
        }

        // if there are no intervals that start small enough, or those intervals do not get us any farther
        if (largestNewEnd == -1 || largestNewEnd <= lastEndPoint) {
          count = -1;
          break;
        }
        else {
          // simulate having picked the interval that had the largest end point
          lastEndPoint = largestNewEnd;
          count++;
          if (lastEndPoint >= l) break; // if crossed the end of the grass, then done!
        }

      }

      cout << count << '\n';

    }
    
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cin.exceptions(cin.failbit); // this throws errors when we dont want to 
  Solution s;
}