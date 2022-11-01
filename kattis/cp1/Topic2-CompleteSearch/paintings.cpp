

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

// #define PI 3.1415926535897932384626433832795

int totalSolutions = 0;
vector<int> theSolution;

void solvePainting(int currentStringPointer, vector<int> remainingStringPointers, string colors[], 
vector<int> pairs1, vector<int> pairs2) {

  // if we havent started yet
  if (currentStringPointer == -1) {
    for (int i = 0; i < remainingStringPointers.size(); i++) {
      // loop through all strings, start a recursive solution with that string as the start

      if (totalSolutions == 0) {
        theSolution.clear();
        theSolution.push_back(remainingStringPointers.at(i));
      }

      vector<int> remainingStringPointersCopy(remainingStringPointers);
      remainingStringPointersCopy.erase(remainingStringPointersCopy.begin() + i);
      int newStringPointer = remainingStringPointers.at(i);
      solvePainting(newStringPointer, remainingStringPointersCopy, colors, pairs1, pairs2);
    }
  }
  // if we have reached a possible solution
  else if (remainingStringPointers.size() == 0) {
    totalSolutions++;
  }
  // if we have started but not finished
  else {
    for (int i = 0; i < remainingStringPointers.size(); i++) {
      // loop through all strings, start a recursive solution with that string as next

      // only make a new thing if the string is allowed to be next to the string
      // interate through all the pairs, check if any of the pairs have "currentStringPointer"
      // if a pair does have currentStringPointer, then check if the other piece of the pair is 
      // remainingStringPointers.at(i); if it is, then we gotta skip this iteration

      bool thisStringAllowedNext = true;
      for (int j = 0; j < pairs1.size(); j++) {
        // cout << "pair: " << pairs1.at(j) << pairs2.at(j) << endl;
        // cout << "pointers: " << currentStringPointer << remainingStringPointers.at(i) << endl;
        if (pairs1.at(j) == currentStringPointer && pairs2.at(j) == remainingStringPointers.at(i)
          || pairs2.at(j) == currentStringPointer && pairs1.at(j) == remainingStringPointers.at(i)
        ) {
          // cout << "This pair is not allowed \n\n";
          // we found a case where this string is not allowed next
          thisStringAllowedNext = false;
          break;
        }
      }

      if (thisStringAllowedNext) {

        if (totalSolutions == 0) {
          theSolution.push_back(remainingStringPointers.at(i));
        }

        vector<int> remainingStringPointersCopy(remainingStringPointers);
        remainingStringPointersCopy.erase(remainingStringPointersCopy.begin() + i);
        int newStringPointer = remainingStringPointers.at(i);
        solvePainting(newStringPointer, remainingStringPointersCopy, colors, pairs1, pairs2);
      }
    }
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  int t;
  cin >> t;

  for (int icase = 0; icase < t; icase++) {

    int n;
    cin >> n;

    // vector<int> colors(n);
    string colors [n]; // dont want to mess with the actual strings
    vector<int> colorPointers;

    for (int i = 0; i < n; i++) {
      // cin >> colors.at(i);
      cin >> colors[i];
      colorPointers.push_back(i);
    }

    int m;
    cin >> m;

    // these are also all pointers to the original string array
    vector<int> pairs1(m); 
    vector<int> pairs2(m);

    for (int i = 0; i < m; i++) {
      string first, second;
      cin >> first;
      cin >> second;

      int j = 0;
      while (j < n) {
        if (colors[j] == first) {
          pairs1.at(i) = j;
        }
        else if (colors[j] == second) {
          pairs2.at(i) = j;
        }
        j++;
      }
    }

    
    // theSolution.reserve(n);
    // call the recursive function
    solvePainting(-1, colorPointers, colors, pairs1, pairs2);

    cout << totalSolutions << "\n";
    string prefix = "";
    for (int i = 0; i < theSolution.size(); i++) {
      cout << prefix << colors[theSolution.at(i)];
      prefix = " ";
    }
    cout << "\n";
    totalSolutions = 0;
    theSolution.clear();



    // output: 
    // total number of possible paintings that are not hideous
    // optimal painting based on color preferences


  }
  
}

// solution:
// iterate through colors
// i want to use recursion because the order should be able to backtrack
// go check notes
// any pruning we can do? not exactly..
// doing an iterative complete search using permuations seems wrong because 
// i would rather build off of what i have
// thats why i want to use recursion, so i build and i backtrack

// call the recursive function with arguments:
// current stringPointer (int)
// remaining stringPointers (vector)

// and i want a global array with the final solution (in integer pointers)
// this solution is set as the first solution because greedy 


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp