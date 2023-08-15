// use well known algorithm of transposing matrix and then reversing rows
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        // transpose:
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 0; j < i; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // reverse rows
        for (int r = 0; r < matrix.size(); r++) {
            reverse(matrix[r].begin(), matrix[r].end());
        }
    }
    
};