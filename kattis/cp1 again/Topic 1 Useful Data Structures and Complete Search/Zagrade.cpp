#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  
  // read the whole line instead of using cin >> ...
  string line;
  getline(cin, line);


  // create a list of tuples, where each tuple contains 
  // start and end parenthesis indeces
  vector<pair<int,int>> listOfTuples;

  // using stack method: push when '(', pop if ')' and add to list of tuples
  stack<int> s;
  for (int i = 0; i < line.length(); i++) {
    char c = line[i];
    if (c == '(') {
      s.push(i);
    }
    else if (c == ')') {
      int startIndex = s.top(); s.pop();
      int endIndex = i;
      listOfTuples.push_back(make_pair(startIndex, endIndex));
    }
    // ignore all other characters
  }
  // listOfTuples is now populated!

  // issue: there could be duplicates
    // line = ((x + y)) --> (x+y) would be outputed twice
  // lets just make a set to get rid of duplicates
  // use ordered set so we dont have to sort lexicographically at the end!
  set<string> outputs;

  // power set algorithm: for every tuple=pair of parenthesis, we can add it or not
  // skip i = 0 because that is the original answer
  for (int i = 1; i < (1 << listOfTuples.size()); i++) {
    // i is a number from 0 to 2^n
    // if you read every bit, you get whether or not to include the tuple
    // read every bit:
    for (int j = 0; j < listOfTuples.size(); j++) {
      // read the jth bit of "i"
      int bitExtractedInt = i & (1 << j);
      bool bitValue = bitExtractedInt != 0;

      // if bitValue true, then include the jth tuple 
      // we can do this by removing the pair of parenthesis from the original string
      if (bitValue) {
        int start = listOfTuples[j].first;
        int end = listOfTuples[j].second;
        line[start] = ' '; // placeholder, will be skipped
        line[end] = ' ';
      }
      else {
        int start = listOfTuples[j].first;
        int end = listOfTuples[j].second;
        line[start] = '(';
        line[end] = ')';
      }
    }

    // delete ' ' from the string before printing (adding to set)
    // create a new string for this
    string current;
    for (char c : line) {
      if (c != ' ') {
        // cout << c;
        current.push_back(c);
      }
    }
    // insert into the set; if its already there, then it will not be inserted again
    outputs.insert(current);
  }

  // print all the sorted strings (note: unordered set automatically sorts)
  for (string s : outputs) {
    cout << s << '\n';
  }

  
}