#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Data {
  int h, t;
  Data() {}
  Data(int h, int t) : h(h), t(t) {}
};

struct Solution {
  Solution() {
    int a, d; cin >> a >> d;

    // populate data of heights and times into vectors
    vector<Data> upData(a);
    vector<Data> downData(d);

    for (int i = 0; i < a; i++) {
      int h, t;
      cin >> h >> t;
      upData[i] = Data(h, t);
    }
    for (int i = 0; i < d; i++) {
      int h, t;
      cin >> h >> t;
      downData[i] = Data(h, t);
    }

    // get total time taken and mountain height by summing up data
    double mountainHeight = 0;
    double totalTimeTaken = 0;
    for (Data d : upData) {
      mountainHeight += d.h;
      totalTimeTaken += d.t;
    }

    // perform 40 iterations of BSTA to find an accurate time
    double low = 0;
    double high = totalTimeTaken;
    double earliestTimeSoFar = high;
    for (int i = 0; i < 40; i++) {
      double potentialTime = low + (high-low) / 2.;
      double upHeight = calculateChangeInElevation(potentialTime, upData);
      double downHeight = mountainHeight - calculateChangeInElevation(potentialTime, downData);

      // they passed each other if the monk going up is higher
      bool passedEachOther = upHeight >= downHeight;
      if (passedEachOther) {
        earliestTimeSoFar = min(earliestTimeSoFar, potentialTime);
        high = potentialTime;
      }
      else {
        low = potentialTime;
      }
    }

    cout << earliestTimeSoFar << '\n';

  }

  // returns delta height after time passed
  double calculateChangeInElevation(double targetTime, vector<Data>& data) {
    if (targetTime == 0) return 0;
    
    double timeElapsed = 0;
    double totalDistance = 0;
    for (Data d : data) {
      // check first if this segment will pass the target time (special case)
      if (timeElapsed + d.t > targetTime) {
        double remainingTime = targetTime - timeElapsed;
        double partialDistance = d.h * (remainingTime / d.t);
        return totalDistance + partialDistance;
      }

      // add this segment to the counters
      timeElapsed += d.t;
      totalDistance += d.h;

      // after handling this segment, if we perfectly landed on target time, then return 
      if (timeElapsed == targetTime) return totalDistance;
    }

    // if the whole loop ended and there is still time left, then we reached the end
    return totalDistance;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}

/*
imagine the up monk and the down monk are 2 different monks
we want to see when they will collide t = ?

BSTA or actually Bisection right? because its continuous: 
give a potential time (between 0 and the full time), 
have the monks passed each other already? true or false --> boolean monotonic --> BSTA

can function: 
figure out where the up monk and the down monk are at a certain time
if down monk is below up monk, they passed each other, so return true
*/