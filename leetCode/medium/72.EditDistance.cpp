// 7/19 review/attempt edit distance again
class Solution {
public:
    int minDistance(string word1, string word2) {

        int dp[word1.length()+1][word2.length()+1];

        // base cases where one of the words is empty
        for (int i = 0; i < word1.length()+1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i < word2.length()+1; i++) {
            dp[0][i] = i;
        }

        for (int i = 1; i < word1.length()+1; i++) {
        for (int j = 1; j < word2.length()+1; j++) {
            
            // note that i and j represent how many characters in the word we are comparing
                // therefore, i = 1 means we should compare the first character (at index 0)

            // the characters match at indeces i-1 and j-1 match
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
                continue;
            }

            // 3 operation cases (when character doesnt match): 
            dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});

        }
        }

        return dp[word1.length()][word2.length()];
    }
};


class Solution {
public:
    int minDistance(string word1, string word2) {

        // lets assume the strings are 1 indexed (so we can set dp 0 to a base case)

        // dp at i, j is 
            // min distance between w1[1 to i] and w2[1 to j]
        // dp at i j =
            // last characters match: dp[i-1][j-1]
            // last characters dont match so replace: 1 + dp[i-1][j-1]
            // delete last character from w1: 1 + dp[i-1] [j]
            // delete last character from w2: 1 + dp[i] [j-1]

        // what should dp be initially?
        // if i (or j) is 0, then dp should be j (or i) because u have to do that many deletes

        // initialize dp
        // +1 because assume 1 indexed, index 0 is base case: string of 0 length
        int dp[word1.length()+1][word2.length()+1];
        for (int i = 0; i < word1.length()+1; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j < word2.length()+1; j++) {
            dp[0][j] = j;
        }

        // build table
        for (int i = 1; i < word1.length()+1; i++) {
            for (int j = 1; j < word2.length()+1; j++) {
                
                // set to 1 if the characters are different 
                int lastCharMatch = word1[i-1] == word2[j-1] ? 0 : 1;

                // last characters match: dp[i-1][j-1]
                // last characters dont match so use 'replace': 1 + dp[i-1][j-1]
                dp[i][j] = lastCharMatch + dp[i-1][j-1];

                // delete last character from w1: 1 + dp[i-1] [j]
                dp[i][j] = min(dp[i][j], 1 + dp[i-1][j]);
                // delete last character from w2: 1 + dp[i] [j-1]
                dp[i][j] = min(dp[i][j], 1 + dp[i][j-1]);
                
            }
        }


        // return dp at i=len1, j=len2 --> min distance between w1[0 to len] and w2[0 to len]

        return dp[word1.length()][word2.length()];

    }
};