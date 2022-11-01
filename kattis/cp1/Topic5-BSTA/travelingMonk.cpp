

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

struct interval {
  int height;
  int time;
};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cout.precision(7);

  int a, d;
  cin >> a >> d;

  // int N = (int)1e5;
  vector<struct interval> ascending;
  vector<struct interval> descending;
  // nums.reserve(N);

  ll totalHeight = 0;

  ll totalTime1 = 0;
  ll totalTime2 = 0;

  for (int i = 0; i < a; i++) {
    int h, t; // height change, and time for that change
    cin >> h >> t;
    // h = 0 when rest and no extra height gained
    struct interval temp = {h, t};
    ascending.push_back(temp);

    totalHeight += h;
    totalTime1 += t;
  }
  
  for (int i = 0; i < d; i++) {
    int h, t; // height change, and time for that change
    cin >> h >> t;

    struct interval temp = {h, t};
    descending.push_back(temp);

    totalTime2 += t;
  }


  // meet in the middle!
  ll h1, h2;
  h1 = 0; h2 = totalHeight;

  ll i1, i2;
  i1 = i2 = 0;

  ll time1, time2;
  time1 = time2 = 0;

  bool lastestMoverIs1 = true;

  while (true) {

    cout << "heights: " << h1 << " " << h2 << endl;
    cout << "times: " << time1 << " " << time2 << endl;

    if (h1 >= h2) {

      cout << "heights have crossed" << endl;

      // double distance, vel1, vel2;


      if (lastestMoverIs1) {
        i1--;
        struct interval path = ascending.at(i1);
        h1 -= path.height;
        time1 -= path.time;
      }
      else {
        i2--;
        struct interval path = descending.at(i2);
        h2 += path.height;
        time2 -= path.time;
      }

      cout << "heights: " << h1 << " " << h2 << endl;
      cout << "times: " << time1 << " " << time2 << endl;

      struct interval asc = ascending.at(i1);
      struct interval desc = descending.at(i2);

      double vel1 = 1.0 * asc.height / asc.time;
      double vel2 = 1.0 * desc.height / desc.time;

      cout << vel1 << " " << vel2 << endl;

      double dist = h2 - h1;

      double t = 1.0 * dist / (vel1 + vel2);

      cout << t << endl;

      //im tired of trying to make this work..










      // struct interval a1 = ascending.at(i1);
      // struct interval a2;

      // struct interval d1 = ascending.at(i2);
      // struct interval d2;

      // if (i1 + 1 == ascending.size()) {
      //   a2.height = totalHeight;
      //   a2.time = 0;
      // }
      // else {
      //   a2 = ascending.at(i1 + 1);
      // }

      // if (i2 + 1 == ascending.size()) {
      //   d2.height = 0;
      //   d2.time = 0;
      // }
      // else {
      //   d2 = descending.at(i2 + 1);
      // }

      // cout << "times: " << d1.time << " " << a1.time << endl;














      // if (i1 - 1 < 0) {
      //   // negative
      //   a1.height = 0;
      //   a1.time = 0;
      // }
      // else {
      //   a1 = ascending.at(i1-1);
      // }

      // if (i2 - 1 < 0) {
      //   // negative
      //   d1.height = totalHeight;
      //   d1.time = 0;
      // }
      // else {
      //   d1 = descending.at(i2-1);

      // }


      

      // vel1 = 1.0 * (a2.height - a1.height) / (a2.time - a1.time);
      // vel2 = 1.0 * (d1.height - d2.height) / (d2.time - d1.time); // switch order to make it positive

      // double newD1Height = 0;
      // double newA1Height = 0;

      // if (a1.time < d1.time) {

      //   newA1Height = a1.height + (d1.time - a1.time) * vel1;

      // }
      // else {
      //   // a1.time  > d1.time
      //   newD1Height = d1.height - (a1.time - d1.time) * vel2;
      // }

      // distance = newD1Height - newA1Height;


      // // cout << distance << " " << vel1 << " " << vel2 << endl;

      // double t;

      // t = distance / (vel1 + vel2);

      // cout << t << endl;


      break;
    }

    // if (i1 == ascending.size()) {
    //   // answer is the greater time
    //   if (totalTime1 > totalTime2) {
    //     cout << totalTime1 << endl;
    //   }
    //   else cout << totalTime2 << endl;
    //   break;
    // }

    // if (i2 == descending.size()) {
    //   // answer is the greater time
    //   if (totalTime1 > totalTime2) {
    //     cout << totalTime1 << endl;
    //   }
    //   else cout << totalTime2 << endl;
    //   break;
    // }

    if (time1 >= time2) {
      lastestMoverIs1 = false;
      struct interval path = descending.at(i2);
      h2 -= path.height;
      time2 += path.time;
      i2++;
    }
    else {
      lastestMoverIs1 = true;
      // cout << "here3" << endl;
      struct interval path = ascending.at(i1);
      h1 += path.height;
      time1 += path.time;
      i1++;
      
    }
    
  }





}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp