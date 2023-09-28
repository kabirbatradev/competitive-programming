class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        

        // bottom up dp approach:
            // dp i, j represents best solution for text[0 to i], text[0 to j]
            // dp[0, 0] is do the first characters match?
        //nvm

        // dp[i, j] represents best solution for text[0 to i-1], text[0 to j-1]
            // dp[0, 0] is before the first character of each string, so 0
        
        int dp[text1.length() + 1][text2.length() + 1];

        // set first row and col to 0
        for (int i = 0; i < text1.length()+1; i++) {
            dp[i][0] = 0;
        }
        for (int i = 0; i < text2.length()+1; i++) {
            dp[0][i] = 0;
        }

        
        // build dp table: 
        // start from i = j = 1, and for each ij, 
            // if the characters match, dp[ij] = dp[i-1j-1] + 1
            // if they dont match, dp[ij] = max(dp[i-1, j] or dp[i,j-1])
        for (int i = 1; i < text1.length()+1; i++) {
            for (int j = 1; j < text2.length()+1; j++) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else 
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }

        return dp[text1.length()][text2.length()];
    }
};