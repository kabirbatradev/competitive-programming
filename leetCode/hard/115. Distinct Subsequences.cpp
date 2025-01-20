class Solution {
public:
    int numDistinct(string s, string t) {

        // edge case: does s have enough of each letter to match t?
        map<char, int> sCounts;
        for (char c : s) {
            sCounts[c]++;
        }
        map<char, int> tCounts;
        for (char c : t) {
            tCounts[c]++;
        }
        for (auto [c, count] : tCounts) {
            if (sCounts[c] < count) return 0;
        }

        long long dp[s.length()+1][t.length()+1];
        
        // base cases:
        // i = 0;
        for (int j = 1; j < t.length()+1; j++) {
            dp[0][j] = 0;
        }
        // j = 0
        for (int i = 0; i < s.length()+1; i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i < s.length()+1; i++) {
            for (int j = 1; j < t.length()+1; j++) {
                // if there are not enough letters left in s to create t, then set 0 early
                // # letters left in s = s.length() - i
                // # letters left to be considered in t: t.length() - j
                if (s.length() - i < t.length() - j) {
                    dp[i][j] = 0;
                    continue;
                }

                if (s[i-1] != t[j-1]) {
                    dp[i][j] = dp[i-1][j]; // cannot use the character
                }
                else {
                    dp[i][j] = 
                        dp[i-1][j-1] // use the character
                        + dp[i-1][j]; // dont use the character
                }
            }
        }

        return (int)dp[s.length()][t.length()];
        
    }
};

/*
for every letter in s, can decide whether we want to use it or not
it cannot be used if it doesnt match the next letter in t
dp problem with inputs:
    # characters matched in t
    # characters used/skipped in s
output: how many ways = distinct subsequences of s that equal t so far

base cases..
dp[0][0]=1 means using 0 characters, how many ways can we get 0 characters of t
if i is 0, then we are using none of s to get characters in t, which is impossible: 0
if j is 0, then we are using characters in s to make no progress in t: 1 way

if characters dont match, then dp[i][j] = dp[i-1][j]
if characters do match, then we have options
    dp[i][j] = dp[i-1][j-1] // use the character
    dp[i][j] = dp[i-1][j] // dont use the character
    these should be summed
*/
