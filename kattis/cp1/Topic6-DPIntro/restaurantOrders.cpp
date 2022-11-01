

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

vector<struct dpAnswer> answerKey;
vector<int> menu;


struct dpAnswer {
  int state; 
  // -1 means not solved, 
  // 0 means impossible
  // 1 means ambiguous
  // 2 means solved
  vector<int> menuItems;
};


struct dpAnswer whatIsTheAnswerLolPleaseTellMe(int question) {

  if (question <= 0) {
    struct dpAnswer youFailed;
    youFailed.state = 0;
    return youFailed;
  }

  struct dpAnswer ans = answerKey.at(question);
  if (ans.state == -1) {
    // solve it!

    // if it is not solved, it will solve itself recursively
    // if it is impossible, the ignore
    // if it is ambiguous, set the state to ambiguous, update the answerkey array, and return
    // if it is solved, check if solved is alr true (if it is, then its ambigious)
    // otherwise, set solved to true, and set menuItems to the previous menu items + the current costMenuItem
    bool alrSolved = false;
    for (int i = 0; i < menu.size(); i++) {
      int costMenuItem = menu.at(i);

      // cout << "checking " << question << " - " << costMenuItem << endl;
      int stateCurrent = whatIsTheAnswerLolPleaseTellMe(question - costMenuItem).state;
      // cout << "for " << question << " - " << costMenuItem << endl;
      // cout << "the state returned: " << stateCurrent << endl;
      if (stateCurrent == 0) {
        continue;
      }
      else if (stateCurrent == 1) {
        // ambig
        ans.state = 1;
        answerKey.at(question) = ans;
        // cout << "we return " << ans.state << endl;
        return ans;
        
      }
      else if (stateCurrent == 2) {
        // if ambiguous because more than 1 solution
        // unless that solution is like 4, 5 vs 5, 4 (then it is still a solution)
        if (alrSolved) {

          // if there was no solution so far:
          // ans.state = 2;
          struct dpAnswer temp;
          temp.menuItems = whatIsTheAnswerLolPleaseTellMe(question - costMenuItem).menuItems;
          temp.menuItems.push_back(i + 1); // index of the menu item
          // sort it and test if it is the same as the solution that alr exists

          // cout << "we have reached a state of alr solved " << question << endl;

          // cout << "temp menu items:" << endl;
          // for (int x : temp.menuItems) {
            // cout << x << " ";
          // }
          // cout << endl;
          // cout << "ans menu items:" << endl;
          // for (int x : ans.menuItems) {
          //   cout << x << " ";
          // }
          // cout << endl;

          if (temp.menuItems.size() == ans.menuItems.size()) {
            sort(temp.menuItems.begin(), temp.menuItems.end());

            sort(ans.menuItems.begin(), ans.menuItems.end());

            for (int j = 0; j < ans.menuItems.size(); j++) {
              if (ans.menuItems.at(j) != temp.menuItems.at(j)) {
                // not the same, so different solutions (ambig)
                ans.state = 1;
                ans.menuItems.clear(); // save memory?????
                answerKey.at(question) = ans;
                // cout << "we return " << ans.state << endl;
                return ans;
              }
            }
            // they are the same!
            // so we do nothing...
            continue;
            
          }
          // otherwise, there is more than one solution
          // set to amg and return
          ans.state = 1;
          ans.menuItems.clear(); // save memory?????
          answerKey.at(question) = ans;
          // cout << "we return " << ans.state << endl;
          return ans;
        }

        // not already solved, so now its solved :D
        alrSolved = true;
        ans.state = 2;
        ans.menuItems = whatIsTheAnswerLolPleaseTellMe(question - costMenuItem).menuItems;
        ans.menuItems.push_back(i + 1); // index of the menu item
        answerKey.at(question) = ans;
        // return ans;
      }
    }
    if (alrSolved) {
      // cout << "we return " << ans.state << endl;
      return ans;
    }
    else {
      // never found a solution
      ans.state = 0;
      answerKey.at(question) = ans;
      // cout << "we return " << ans.state << endl;
      return ans;
    }
    
  }
  else {
    // cout << "we return " << ans.state << endl;
    return ans;
  }

}


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  // initialize the dp array
  answerKey.reserve(30001); // we start from 1 for easier output

  vector<int> empty;
  struct dpAnswer notSolved = {-1, empty};

  for (int i = 0; i < 30001; i++) {
    answerKey.push_back(notSolved);
  }



  int n;
  cin >> n;
  // int N = (int)1e5;
  menu.reserve(n);
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    menu.push_back(c);
    // check if it is already solvable (if not, then set to solvable)
    // if it is, then set ambig
    struct dpAnswer temp = whatIsTheAnswerLolPleaseTellMe(c);
    if (temp.state == 0) {
      // not solved (so it is solvable by c)
      answerKey.at(c).state = 2;
      answerKey.at(c).menuItems.push_back(i + 1);

    }
    else if (temp.state == 1) {
      // ambig
      answerKey.at(c).state = 1;

    }
    else if (temp.state == 2) {
      // solved, which means its actually ambig
      answerKey.at(c).state = 1;

    }
  }

  int m;
  cin >> m;
  // vector<int> orders;
  // orders.reserve(m);
  

  // iterate through the orders
  for (int i = 0; i < m; i++) {
    int o;
    cin >> o;
    // orders.push_back(o);

    if (menu.size() == 1) {
      if (o % menu.at(0) == 0) {
        string prefix = "";
        for (int x = 0; x < o / menu.at(0); x++) {
          cout << prefix << "1";
          prefix = " ";
        }
        cout << "\n";
        continue;
      }
    }

    struct dpAnswer theAnswer = whatIsTheAnswerLolPleaseTellMe(o);
    // for (int j = 0; j < 15; j++) {
      // cout << answerKey.at(j).state << " ";
    // }
    // cout << endl;
    switch (theAnswer.state) {
      case 0:
      {
        cout << "Impossible\n";
        break;
      }
      case 1:
      {
        cout << "Ambiguous\n";
        // string prefix = "";
        // sort(theAnswer.menuItems.begin(), theAnswer.menuItems.end());
        // for (int i : theAnswer.menuItems) {
        //   cout << prefix << i;
        //   prefix = " ";
        // }
        // cout << "\n";
        break;
      }
      case 2:
      {
        string prefix = "";
        sort(theAnswer.menuItems.begin(), theAnswer.menuItems.end());
        for (int i : theAnswer.menuItems) {
          cout << prefix << i;
          prefix = " ";
        }
        cout << "\n";
        break;
      }
      
      // you can have any number of case statements.
      default : //Optional
        // there was an error
        break;
    }

  }

  // youre dead to me

  // omaeof woo shiendeirju nani = grandmother

  


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp