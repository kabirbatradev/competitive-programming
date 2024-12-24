class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]) {
                    // visited[i][j] = true;
                    if (dfs(i, j, 1, board, visited, word)) {
                        return true;
                    }
                    // visited[i][j] = false;
                }
            }
        }

        return false;
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    bool dfs(int i, int j, int charPos, 
        vector<vector<char>>& board, vector<vector<bool>>& visited,
        string& word
    ) {
        if (charPos == word.length()) return true;
        visited[i][j] = true;

        for (int k = 0; k < 4; k++) {
            int i2 = i + dx[k];
            int j2 = j + dy[k];

            // out of bounds or visited already or character on board does not match
            if (i2 < 0 || j2 < 0 || i2 >= board.size() || j2 >= board[0].size()
            || visited[i2][j2] || board[i2][j2] != word[charPos]) {
                continue;
            }

            if (dfs(
                i2, j2, charPos+1, board, visited, word
            )) return true;
        }

        visited[i][j] = false;
        return false;

    }
};