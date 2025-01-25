#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  
  string line;
  getline(cin, line);


  int n; cin >> n;
  cin.ignore();

  vector<vector<string>> allParsedStrings(n);

  for (int i = 0; i < n; i++) {
    getline(cin, line);

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

  // now compare every string to every string
  // store the max diff for every line


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

      maxDiff[i] = max(maxDiff[i], diffCounter);
      maxDiff[j] = max(maxDiff[j], diffCounter);
    }
  }

  vector<int> indecesWithMinMaxDiff;
  int leastMaxDiff = maxDiff[0];
  for (int i = 0; i < maxDiff.size(); i++) {
    int diff = maxDiff[i];
    if (diff == leastMaxDiff) {
      indecesWithMinMaxDiff.push_back(i);
    }
    else if (diff < leastMaxDiff) {
      leastMaxDiff = diff;
      indecesWithMinMaxDiff.clear();
      indecesWithMinMaxDiff.push_back(i);
    }
  }

  // regenerate the strings and print them
  for (int index : indecesWithMinMaxDiff) {
    vector<string>& pieces = allParsedStrings[index];
    string prefix = "";
    for (string substring : pieces) {
      cout << prefix << substring;
      prefix = ", ";
    }
    cout << '\n';
  }


}