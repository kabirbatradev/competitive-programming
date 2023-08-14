class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {

        int rows = grid.size();
        int cols = grid.at(0).size();

        // min and second min of every row
        // and min's index so if the index is the same, we can do the second min
        int mins[rows];
        int minIndex[rows];
        int secondMins[rows];
        for (int i = 0; i < rows; i++) {
            mins[i] = secondMins[i] = INT_MAX;
        }

        // start from last row (bc nothing below)
        int row = grid.size() - 1;
        for (int col = 0; col < cols; col++) {
            int val = grid.at(row).at(col);

            if (val < secondMins[row]) {
                if (val < mins[row]) {
                    // set second min to min
                    // update min and min index
                    secondMins[row] = mins[row];
                    mins[row] = val;
                    minIndex[row] = col;
                }
                else {
                    // do not update min
                    // update second min
                    secondMins[row] = val;
                }
            }
        }

        // for the rest of the rows:
        // use the previous row's min or second min (if same column)
        for (row = grid.size() - 2; row >= 0; row--) {
            for (int col = 0; col < cols; col++) {
                int val = grid.at(row).at(col);
                // val should include the minimum sum we can use from the next row
                
                if (minIndex[row+1] != col) {
                    // not the same index, so we can use min
                    val += mins[row+1];
                }
                else {
                    // same index so we cannot use min
                    val += secondMins[row+1];
                }

                if (val < secondMins[row]) {
                    if (val < mins[row]) {
                        // set second min to min
                        // update min and min index
                        secondMins[row] = mins[row];
                        mins[row] = val;
                        minIndex[row] = col;
                    }
                    else {
                        // do not update min
                        // update second min
                        secondMins[row] = val;
                    }
                }
            }
        }

        // finally, return first row's min
        return mins[0];        
    }
};