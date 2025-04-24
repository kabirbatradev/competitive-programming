#include <bits/stdc++.h>
#define int long long
// #define INT_MAX LLONG_MAX
#define INF 1e18
using namespace std;

// int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
// int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

struct Solution {
  Solution() {
    int n, f; cin >> n >> f;
    // f: threshold such that it could have been bessie

    string s; cin >> s;

    // detect all moos
    using moo = tuple<char, char, char>;
    map<moo, int> counter;
    for (int i = 0; i < n-2; i++) {
      char c1 = s[i];
      char c2 = s[i+1];
      char c3 = s[i+2];

      // cout << c1 << c2 << c3 << '\n';
      
      // if moo, add to counter
      if (c1 != c2 && c2 == c3) {
        counter[{c1, c2, c3}]++;
      }
    }

    // cout << endl;
    // for (auto [m, count] : counter) {
    //   // if (count >= f) {
    //     auto [c1, c2, c3] = m;
    //     cout << c1 << c2 << c3 << '\n';
    //     cout << count << '\n';
    //   // }
    // }
    // cout << endl;


    // second pass: if we can change 1 character to make something a moo
    // and by changing that character, it crosses the threshold,
    // then this is a new moo
    for (int i = 0; i < n-2; i++) {
      char c1 = s[i];
      char c2 = s[i+1];
      char c3 = s[i+2];

      // if (c1 == 'c' && c2 == 'q' && c3 == 'q') {
      //   cout << "   cqq detected at index = " << i << endl;
      // }

      vector<pair<moo,int>> potential; // potential new moos
      // and the index of the character that was changed
      
      // if second and third are same
      if (c2 == c3) {
        for (char newC1 = 'a'; newC1 <= 'z'; newC1++) {
          if (newC1 == c1) continue; // skip the current c1 case
          potential.push_back({{newC1, c2, c3}, i});
        }
      }

      // if not alr moo and ... 
      if (!(c1 != c2 && c2 == c3)) {

        if (c1 != c2) {
          char newC3 = c2;
          potential.push_back({{c1, c2, newC3}, i+2});
        }
  
        if (c1 != c3) {
          char newC2 = c3;
          potential.push_back({{c1, newC2, c3}, i+1});
        }

      }
      

      // for every potential new moo:
      // 'index' is the index of the character that was modified 
      for (auto [m, index] : potential) {

        // dont consider it if its not going to barely push the counter over
        if (counter[m] != f-1) {
          continue;
        }


        // cout << "potential at index = " << i << endl;
        // auto [p1, p2, p3] = m;
        // cout << "potential string is " << p1 << p2 << p3 << '\n';


        

        // this moo is invalidated if we ruined an identical moo by changing this character
        // check 3 moos around 'index' 
        // case1: this char, next, next
        if (index + 2 < n) { // check in bounds first
          char cc1 = s[index];
          char cc2 = s[index+1];
          char cc3 = s[index+2];
          moo m2 = {cc1, cc2, cc3};
          if (m == m2) {
            // cout << "invalid 1" << endl;
            continue;
          }
        }
        // case2: prev char, this, next
        if (index-1 >= 0 && index + 1 < n) { // check in bounds first
          char cc1 = s[index-1];
          char cc2 = s[index];
          char cc3 = s[index+1];
          moo m2 = {cc1, cc2, cc3};
          if (m == m2) {
            
            // cout << "invalid 2" << endl;

            // cout << "at this index, characters are " << s[index-1] << s[index] << s[index+1] << '\n';

            continue;
          }
        }
        // case3: prev prev char, prev char, this
        if (index-2 >= 0) { // check in bounds first
          char cc1 = s[index-2];
          char cc2 = s[index-1];
          char cc3 = s[index];
          moo m2 = {cc1, cc2, cc3};
          if (m == m2) {
            // cout << "invalid 3" << endl;

            continue;
          }
        }

        // cout << "not invalididated" << endl;


        // if we are just under the threshold,
        // this is a new potential moo
        // if (counter[m] == f-1) {
          counter[m]++;
        // }

        
      }
    }


    // find all moos that beat the threshold and print
    int total = 0;
    for (auto [m, count] : counter) {
      if (count >= f) {
        total++;
        // auto [c1, c2, c3] = m;
        // cout << c1 << c2 << c3 << '\n';
        // cout << count << '\n';
      }
    }
    cout << total << '\n'; // print total that meet threshold first
    for (auto [m, count] : counter) {
      if (count >= f) {
        auto [c1, c2, c3] = m;
        cout << c1 << c2 << c3 << '\n';
      }
    }



  }
};

signed main() {
  std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  // cout.precision(1); cout << fixed; // # decimal places

  // int t; cin >> t;
  // for (int i = 0; i < t; i++) 
    Solution s;
}

/*
string contains potential "moo"s
goal: 
  keep track of how many different moo variations there are
  and how many there are of each
  if there are more than 'f' variations, then we need to print it

  also, if 1 character is changed to turn something into a moo, and
  now that particular moo has a count of exactly f (it crossed the threshold),
  then that moo should be included 
  
we could do this by:
  go through every window of 3 letters
  check if it is a moo
    if so, add to a counter
  
  second pass:
    go through every window of 3 characters

    if this is a moo already: restated: second and third are the same
      we can just change the first character to every other character
    if not moo and:
    if first and second char are different
      change the third char to make it a moo

    if first and third are different
      change the second char to make it a moo

    if second and third are same
      this is just the "already moo case", except its like "ooo"
      we can group this with the already moo case
    
    for every potential moo after changing some character:
      check the count of that current moo
      if it is one less than the threshold, then increment it
        because now that is a possible moo
      otherwise, either changing that one character is not enough...
        wait but what if one character change makes 2 new moos?
          if they are distinct moos, then we would have detected it
          is it possible to change 1 char and create 2 of the same moos
           no
      or that moo was already well established and we were already going to print it out

finally, go through all moo's detected, and if the count is at least F, then
print them in alphabetical order (use an ordered map as the counter)

edge case:
  by changing a character we created the moo "ozz"
  but we also killed a preexisting "ozz"
  so by changing the character, we didnt actually create a new ozz

solution:
  when changing the character, we also have to check if we destroyed a 
  preexisting moo
  if its the same moo, then this new moo doesnt count
how do we check if we destroyed a preexisting moo
  check all 3 moos that could have been made that include this character
  this character is on the left, middle, or right
  skip if out of bounds
  if before changing the character, we could have made the same moo
  with that same character position, then this moo is invalidated

*/