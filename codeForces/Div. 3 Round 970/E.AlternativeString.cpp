#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int t; cin >> t;
  for (int tc = 0; tc < t; tc++) {
		int n; cin >> n;
		string s; cin >> s;
		// cout << "n = " << n << ":\t";
		if (n % 2 == 0) {
			// frequency table for evens and odds
			// int evens[26] = {0};
			// int odds[26] = {0};
			int both[2][26] = {{0}, {0}};
			for (int i = 0; i < n; i++) {
				char c = s[i];
				// if (i % 2 == 0) {
				// 	evens[c - 'a']++;
				// }
				// else {
				// 	odds[c - 'a']++;
				// }
				both[i % 2 == 1][c - 'a']++;
			}

			// find the most popular evens letter and odds letter
			int evenBest = 0;
			int oddBest = 0;
			for (int i = 0; i < 26; i++) {
				// evenBest = max(evens[i], evenBest);
				// oddBest = max(odds[i], oddBest);
				evenBest = max(both[0][i], evenBest);
				oddBest = max(both[1][i], oddBest);
			}
			// number of modifications = number of characters that don't align with even best and odd best
			cout << n - evenBest - oddBest << "\n";
		}
		else {
			// cout << "else" << 0 << "\n";

			// left side even odd, right side even odd
			// try deletion on every possible character, modify frequency table as we iterate
			int left[2][26] = {{0}, {0}};
			int right[2][26] = {{0}, {0}};

			// initialize right table with everything except first character
			for (int i = 1; i < n; i++) {
				char c = s[i];
				right[i % 2 == 1][c - 'a']++;
			}

			// try deletion on every character, adjust frequency tables, store best case
			int bestCase = n;
			for (int i = 0; i < n; i++) {
				if (i == 0) {
					// no modification to freq tables
				}
				else {
					left[(i-1) % 2 == 1][s[i-1] - 'a']++; // add prev letter to left freq tables
					right[i % 2 == 1][s[i] - 'a']--; // remove current letter from right freq tables
				}

				// note that evens on the left are odds on the right because of the deleted ith character
				// find the most popular evens letter and odds letter
				int evenBest = 0;
				int oddBest = 0;
				for (int i = 0; i < 26; i++) {
					evenBest = max(left[0][i] + right[1][i], evenBest);
					oddBest = max(left[1][i] + right[0][i], oddBest);
				}
				// number of modifications = number of characters that don't align with even best and odd best
				int potentialBest = n-1 - evenBest - oddBest; // -1 because dont want to count the deleted
				bestCase = min(bestCase, potentialBest);
			}
			cout << bestCase+1 << "\n"; // +1 because modification of deletion

		}

  }
}