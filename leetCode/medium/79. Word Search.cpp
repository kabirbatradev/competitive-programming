class Solution {
public:

    // global visited array (represents if something is already a part of the current word)
    vector<vector<bool>> visited;

    bool exist(vector<vector<char>>& board, string word) {
        // looks like basic backtracking
        // no major optimizations i can think of

        for (int i = 0; i < board.size(); i++) {
            visited.push_back({});
            for (int j = 0; j < board[0].size(); j++) {
                visited[i].push_back(false);
            }
        }

        // for every position on the board, try doing dfs
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {

                if(dfs(i, j, board, word, 0)) return true;
                
            }
        }

        // tried starting from every position but it all failed
        return false;
        
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    bool dfs(int i, int j, vector<vector<char>>& board, string& word, int index) {

        

        // if ij is in a visited part of the current word, then cannot continue in that direction
        // if (visited[i][j]) return false;

        // if the letter at ij does not match the word at index, then fail
        if (board[i][j] != word[index]) return false;

        // if this character was the last one, then yay we win
        if (index == word.size()-1) return true;
        
        // continue dfs in all directions, maintain visited array
        // set current position as visited
        visited[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int newi = i + dx[k];
            int newj = j + dy[k];

            // make sure newi and newj are not out of range
            if (newi < 0 || newi == board.size() || newj < 0 || newj == board[0].size()) continue;

            // make sure new is not already visited (skip if is)
            if (visited[newi][newj]) continue;

            if (dfs(newi, newj, board, word, index+1)) return true;
        }
        // undo set current position as visited
        visited[i][j] = false;

        return false; // tried all 4 directions but they all failed
    }
};