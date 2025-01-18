class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        bool firstRowZero = false;
        for (int i = 0; i < m; i++) {
            if (matrix[0][i] == 0) {
                firstRowZero = true;
                break;
            }
        }

        bool firstColZero = false;
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {

                if (matrix[i][j] == 0) {

                    // mark it with the first row/col
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                    
                }
            }
        }

        // fill in all rows and cols that have marked zeros
        for (int i = 1; i < n; i++) {
            if (matrix[i][0] != 0) continue;
            for (int j = 1; j < m; j++) {
                matrix[i][j] = 0;
            }
        }
        for (int j = 1; j < m; j++) {
            if (matrix[0][j] != 0) continue;
            for (int i = 1; i < n; i++) {
                matrix[i][j] = 0;
            }
        }

        // fill in first row and col if those flags are true
        if (firstRowZero) {
            for (int i = 0; i < m; i++) {
                matrix[0][i] = 0;
            }
        }
        if (firstColZero) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
            }
        }
        
    }
};