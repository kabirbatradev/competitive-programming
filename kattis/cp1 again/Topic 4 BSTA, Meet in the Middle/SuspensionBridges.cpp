#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {
  Solution() {
    int d, s; cin >> d >> s;

    // goal: find param 'a' such that the equation is true
      // a + s = a * cosh( d/(2a) )
    // can use BSTA to find this param
      // bounds: graphing the problem in desmos, we get 0 to 125000
    // graphing LHS and RHS separately and looking at the behavior left and right of intersection point:
      // if LHS > RHS, then make x smaller
      // else: make x bigger
    // then get length using this equation
      // length = 2a * sinh( d/(2a) )
    
    double low = 0.;
    double high = 125000. * 2; // expand range just in case
    for (int i = 0; i < 100; i++) { // increase # iterations just in case

      double mid = low + (high - low) / 2.0;

      if (LHS(mid, s, d) > RHS(mid, s, d)) {
        high = mid;
      }
      else {
        low = mid;
      }
    }

    cout << getLength(low, s, d) << '\n';

  }

  double LHS(double a, double s, double d) {
    return a + s;
  }

  double RHS(double a, double s, double d) {
    return a * cosh( d/(2.*a) );
  }

  double getLength(double a, double s, double d) {
    return 2.*a * sinh( d/(2.*a) );
  }

};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  cout.precision(15); // print large precision
  Solution s;
}