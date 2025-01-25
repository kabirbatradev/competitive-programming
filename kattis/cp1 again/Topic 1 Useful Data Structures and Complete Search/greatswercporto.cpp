#include<bits/stdc++.h>
using namespace std;

vector<char> uniqueCharList;
unordered_set<char> uniqueCharSet;
// unordered_map<char, int> charToValue;
int charToValue[26];
unordered_set<char> firstLetters;
vector<string> words;
vector<bool> usedDigits(10, false);

int numSolutions = 0;

void dfs(int);

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);


  int n; cin >> n;

  for (int i = 0; i < n; i++) {
    string word; cin >> word;
    words.push_back(word);
    for (int i = 0; i < word.length(); i++) {
      char c = word[i];
      if (!uniqueCharSet.count(c)) {
        uniqueCharList.push_back(c);
        uniqueCharSet.insert(c);
      }
      if (i == 0) {
        firstLetters.insert(c);
      }
    }
  }

  dfs(0);
  cout << numSolutions << '\n';
  return 0;
}

void dfs(int charIndex) {
  // all chars have been assigned a value:
  if (charIndex == uniqueCharList.size()) {
    // check if the equation is valid

    int sum = 0;
    for (int i = 0; i < words.size(); i++) {
      string& word = words[i];
      int wordValue = 0;
      for (int j = 0; j < word.length(); j++) {
        wordValue *= 10;
        wordValue += charToValue[word[j] - 'A'];
      }
      // if not the last word
      if (i != words.size()-1) {
        sum += wordValue;
      }
      else {
        if (sum == wordValue) {
          numSolutions++;
        }
      }
    }
    return;
  }

  // assign current char to every possible digit
  char currChar = uniqueCharList[charIndex];

  for (int i = 0; i <= 9; i++) {
    // check if we should skip setting it to 0
    if (i == 0 && firstLetters.count(currChar)) continue;
    if (usedDigits[i]) continue;
    charToValue[currChar - 'A'] = i;
    usedDigits[i] = true;
    dfs(charIndex + 1);
    usedDigits[i] = false;
  }
}