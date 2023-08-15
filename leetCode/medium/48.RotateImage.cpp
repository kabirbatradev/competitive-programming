// using my own algorithm instead of
// transpose + reverse rows
class Solution {
public:
    int n;
    void rotate(vector<vector<int>>& matrix) {
        n = matrix.size();

        // test to see if rotatePosition() works: 

        // int m[n][n];
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         cout << matrix[i][j] << " ";
        //         int r = i, c = j;
        //         rotatePosition(r, c, n);
        //         m[r][c] = matrix[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         cout << m[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // only use halfN once if n is odd (rotate top 2x1 grid out of 3x3 grid)
        int halfN = n / 2 + (n%2==0 ? 0 : 1);

        // iterate half way through matrix
        for (int i = 0; i < halfN; i++) {
            for (int j = 0; j < n/2; j++) {
                // rotate 4 times and swap 4 times
                int r = i, c = j;

                int prevVal = matrix[r][c];
                
                for (int k = 0; k < 4; k++) {
                    rotatePosition(r, c);
                    int nextVal = matrix[r][c];
                    matrix[r][c] = prevVal;
                    prevVal = nextVal;
                }

            }
        }

    }

    void rotatePosition(int& row, int& col) {
        int half = n / 2;
        // translate origin to center
        row -= half; // 0 -> -2
        col -= half; // 3 -> 1 -> 2
        // if n is even and row/col is >= 0, add 1 to row/col
        if (n % 2 == 0) {
            if (row >= 0) row++;
            if (col >= 0) col++;
        }

        // swap x and y
        row ^= col;
        col ^= row;
        row ^= col;

        // negate x
        col *= -1;

        // now reverse the translation:

        // if half is even and row/col is >= 0, subtract 1
        if (n % 2 == 0) {
            if (row >= 0) row--;
            if (col >= 0) col--;
        }
        row += half;
        col += half;
    }
};