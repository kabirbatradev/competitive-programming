// // Author: Kabir Batra
// // It is okay to share my code for educational purposes

// #include <bits/stdc++.h>
// // using ll = long long;
// #define int long long // replace all "int" with "long long"
// using namespace std;

// struct Solution {
//   Solution() {
//     int n; cin >> n;

//     // put pairs into set (camel position, spat at position)
//     // if reversed pair is already in the set, then a camel exists that spat at this one
//     // set<pair<int, int>> s;
//     map<int, int> s;
//     for (int i = 0; i < n; i++) {
//       int x, d; cin >> x >> d;
//       int x2 = x + d;
//       // if (s.contains({x2, x})) { // doesnt work in old compiler (feature of cpp 20)
//       // if (s.count({x2, x})) {
//       auto it = s.find(x2);
//       if (it != s.end() && it->second == x) {
//         cout << "YES" << '\n';
//         return; // end the test case
//       }
//       s[x] = x2;
//     }

//     // if we got here, we found no matches
//     cout << "NO" << '\n';
//   }
// };

// // using "signed" works around "int" being replaced with long long
// signed main() {
//   // std::ios::sync_with_stdio(false);
//   // cin.tie(0); cout.tie(0);
//   // cin.exceptions(cin.failbit); // idk what this does but it prevents me from doing while (cin >> n)
//   // cout.precision(1); // # decimal places
//   // cout << fixed; // force precision decimal places
//   int t; cin >> t;
//   for (int i = 0; i < t; i++)
//     Solution s;
// }




/*
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
  int t; cin >> t;
  for (int i = 0; i < t; i++) {
    int n; cin >> n;
    map<int, int> m;
    bool found = false;
    for (int j = 0; j < n; j++) {
      int x, d; cin >> x >> d;
      m[x] = x+d;
      auto it = m.find(x+d);
      if (it != m.end() && it->second == x) {
        found = true;
        break;
      }
    }
    cout << (found ? "YES" : "NO") << endl;
  }
}
*/




#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
  int t; cin >> t;
  for (int i = 0; i < t; i++) {
    int n; cin >> n;
    map<int, int> m;
    bool found = false;
    for (int j = 0; j < n; j++) {
      int x, d; cin >> x >> d;
      m[x] = x+d;
    }
    for (auto [x, x2] : m) {
      auto it = m.find(x2);
      if (it != m.end() && it->second == x) {
        found = true;
        break;
      }
    }

    cout << (found ? "YES" : "NO") << endl;
  }
}