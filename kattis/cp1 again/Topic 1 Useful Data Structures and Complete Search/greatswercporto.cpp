// Author: Kabir batra
// It is okay to share my code for educational purposes

#include<bits/stdc++.h>
using namespace std;

vector<char> uniqueCharList;
unordered_set<char> uniqueCharSet;
// unordered_map<char, int> charToValue;
int charToValue[26]; // using an array to map char -> val is much faster 
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

    // keep track of all the words
    words.push_back(word);

    // update set of all unique characters that showed up
    // update set of all "first letters" that cannot be assigned to 0
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

  // start with first requesting to assign the first character
  dfs(0);
  cout << numSolutions << '\n';
  return 0;
}

// idea: assign each character to some value
// if we found a solution, increment global counter numSolutions
// backtrack if all characters are assigned

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
      // if not the last word, then increment sum
      if (i != words.size()-1) {
        sum += wordValue;
      }
      // if last word, then check if last word value = total sum
      else {
        if (sum == wordValue) {
          numSolutions++;
        }
      }
    }
    return;
  }
  // otherwise, not all characters have been assigned
  // assign current (aka next) char to every possible digit
  char currChar = uniqueCharList[charIndex];

  // 10 possible values to assign
  for (int i = 0; i <= 9; i++) {
    // check if we should skip setting it to 0 because its a "first character" in a word
    if (i == 0 && firstLetters.count(currChar)) continue;
    // skip if digit already used
    if (usedDigits[i]) continue;
    charToValue[currChar - 'A'] = i; // set the mapping char->value
    usedDigits[i] = true; // this digit is now marked as used
    dfs(charIndex + 1); // request to assign the next character
    usedDigits[i] = false; // unmark digit as used to allow it to be used in other backtracking branches
  }
}