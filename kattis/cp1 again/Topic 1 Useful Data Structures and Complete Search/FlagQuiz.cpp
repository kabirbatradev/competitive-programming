// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  
  // discard first line; the question is not relevant
  string line;
  getline(cin, line);

  int n; cin >> n;
  cin.ignore(); // ignore "\n" after the integer

  // store all broken up strings in this:
  vector<vector<string>> allParsedStrings(n);

  for (int i = 0; i < n; i++) {
    getline(cin, line);

    // break up the string by searching for commas, store in ith position of allParsedStrings
    vector<string>& strings = allParsedStrings[i];

    int start = 0;
    int j;
    for (j = 0; j < line.length(); j++) {
      if (line[j] == ',') {
        strings.push_back(line.substr(start, j - start));
        start = j+2;
      }
    }
    strings.push_back(line.substr(start, j - start));
  }
  // parsed all the strings! yay

  // now compare every string to every string (all pairs)
  // store the max diff for each

  vector<int> maxDiff(n);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {

      int diffCounter = 0;

      vector<string>& a = allParsedStrings[i];
      vector<string>& b = allParsedStrings[j];
      for (int k = 0; k < a.size(); k++) {
        if (a[k] != b[k]) {
          diffCounter++;
        }
      }

      // update max difference of both strings behing compared
      maxDiff[i] = max(maxDiff[i], diffCounter);
      maxDiff[j] = max(maxDiff[j], diffCounter);
    }
  }

  // find all of the strings that have the minimum "max diff"
  // store the indices of the strings in indecesWithMinMaxDiff
  vector<int> indecesWithMinMaxDiff;
  int leastMaxDiff = maxDiff[0];
  for (int i = 0; i < maxDiff.size(); i++) {
    int diff = maxDiff[i];
    if (diff == leastMaxDiff) {
      indecesWithMinMaxDiff.push_back(i);
    }
    // we found a new maxDiff that is smaller than all previous, so clear the vector 
    else if (diff < leastMaxDiff) {
      leastMaxDiff = diff;
      indecesWithMinMaxDiff.clear();
      indecesWithMinMaxDiff.push_back(i);
    }
  }

  // regenerate the strings that have the minimum "max diff" and print them
  for (int index : indecesWithMinMaxDiff) {
    vector<string>& pieces = allParsedStrings[index];
    string prefix = ""; // prefix trick to not print extra comma at the end
    for (string substring : pieces) {
      cout << prefix << substring;
      prefix = ", ";
    }
    cout << '\n';
  }


}