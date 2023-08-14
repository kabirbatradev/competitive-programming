// TLE: this solution is brute force

class Position {
public:
    int row, col;
    Position(int row, int col) : row(row), col(col) {}
};

class Solution {
public:

    int minSum;

    int minFallingPathSum(vector<vector<int>>& matrix) {
        // reason for not doing greedy is it is possible to greedily go down the wrong path

        // brute force:
        // traverse every falling path and save minimum falling path

        minSum = INT_MAX;

        // for every column, start a falling path
        for (int i = 0; i < matrix.at(0).size(); i++) {
            traverse(0, Position(0, i), matrix);
        }
        
        return minSum;

    }

    void traverse(int sumSoFar, Position pos, vector<vector<int>>& grid) {

        // if last row, then compare sum to best sum and do not recurse
        if (pos.row == grid.size()-1) {
            if (sumSoFar + grid.at(pos.row).at(pos.col) < minSum) {
                minSum = sumSoFar + grid.at(pos.row).at(pos.col);
            }
            return;
        }

        // update sum with grid position
        sumSoFar += grid.at(pos.row).at(pos.col);
        for (int i = -1; i <= 1; i++) {
            // if in range
            if (0 <= pos.col + i && pos.col + i < grid.at(0).size()) {
                // update new position
                Position newPos = Position(pos.row+1, pos.col+i);
                // pos.row += 1;
                // pos.col += i;
                // note that the Position does not automatically get cloned
                traverse(
                    sumSoFar,
                    newPos,
                    grid
                );
            }
        }
        return;
    }
};