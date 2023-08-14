class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        // new perspective:
        // build up from the bottom 
            // calculate the minimum if we start from some position
            // use that for the next row up instead of doing repeated computation

        int rows = matrix.size(), cols = matrix.at(0).size();

        // grid to keep track of minSums as we build up the table
        int minSums[rows][cols];

        // start from last row, calculate min sum from previous row

        // last row:
        int row = rows-1;
        // for every pos in last row, fill in minSum as val
        for (int col = 0; col < cols; col++) {
            minSums[row][col] = matrix[row][col];
        }

        // rows after
        for (int row = rows-1-1; row >= 0; row--) {
            // for every pos in row, minSum = val + minSum of next row 3 possibilites
            for (int col = 0; col < cols; col++) {
                
                int minVal = INT_MAX;
                for (int i = -1; i <= 1; i++) {
                    // if in range, then get minSum from next row
                    if (0 <= col+i && col+i < cols) {
                        if (minSums[row+1][col+i] < minVal) 
                            minVal = minSums[row+1][col+i];
                    }
                }

                minSums[row][col] = matrix[row][col] + minVal;
            }
        }

        int minSum = INT_MAX;
        row = 0;
        for (int col = 0; col < cols; col++) {
            if (minSums[row][col] < minSum)
                minSum = minSums[row][col];
        }

        return minSum;

    }
};