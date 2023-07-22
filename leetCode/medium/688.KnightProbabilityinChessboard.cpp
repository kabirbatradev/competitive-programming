class Solution {
public:
    // k, row, column
    double dp[101][26][26]; // 0 by default
    // 0 also happens when all 8 moves go off the board

    double knightProbability(int n, int k, int row, int column) {

        // initialize table to -1
        for (int a = 0; a < 101; a++) {
            for (int b = 0; b < 26; b++) {
                for (int c = 0; c < 26; c++) {
                    dp[a][b][c] = -1;
                }
            }
        }

        // run separate function (so we dont keep reinitializing the table)
        return recursive(n, k, row, column);
        
    }

    double recursive(int n, int k, int row, int column) {
        // if alr in the cache, return that
        if (dp[k][row][column] != -1) 
            return dp[k][row][column];
        
        // if out of moves, (assuming row col is valid), return probability = 1
        if (k == 0) {
            return 1.;
        }
        
        // sum probability of 8 different directions knight can move
        double ans = 0;
        int drow[8] = {2, 2, 1, -1, -2, -2, -1, 1}; 
        int dcol[8] = {1, -1, -2, -2, -1, 1, 2, 2}; 
        for (int i = 0; i < 8; i++) {
            int r = row + drow[i]; 
            int c = column + dcol[i]; 

            if (r < 0 || c < 0 || r >= n || c >= n) {
                ans += 0;
                continue;
            }
            ans += recursive(n, k-1, r, c);
        }

        // divide by 8 to get valid moves / total moves
        ans = ans/8.;

        // store answer in cache
        dp[k][row][column] = ans;

        return ans;
    }
    
};