class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        unordered_set<char> rows[9];
        unordered_set<char> cols[9];
        
        unordered_set<char> current_box;

        // take less memory by doing rows, columns and boxes separately, eaching using
        // only 1 set

        // for every big box
        for (int box = 0; box < 9; box++) {
            current_box.clear();
            int offsetX = box % 3;
            int offsetY = box / 3;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int x = i + offsetX*3;
                    int y = j + offsetY*3;

                    char val = board[y][x];
                    if (val == '.') continue; // skip empties

                    if (current_box.count(val) != 0) return false;
                    if (rows[y].count(val) != 0) return false;
                    if (cols[x].count(val) != 0) return false;

                    current_box.insert(val);
                    rows[y].insert(val);
                    cols[x].insert(val);
                }
            }
        }

        return true;
    }
};