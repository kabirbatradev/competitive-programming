struct CharNode {
    map<char, CharNode *> children;
    bool end = false;
    string word; // only exists if is end of word; for quick access
    CharNode *parent = nullptr;
    CharNode(CharNode *parent) : parent(parent) {}
};

class Solution {
public:
    CharNode *root;
    // map<char, CharNode *> trie;
    vector<string> found;
    // set<string> found;
    int n, m;

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        // new attempt: bring back deletion, but only delete current node from parent's list

        n = board.size();
        m = board[0].size();

        // found = 0;

        // create trie 
        root = new CharNode(nullptr);
        // trie --> root->children
        
        for (string& word : words) {

            CharNode *current = nullptr;
            // find the first char in the map
            if (root->children.count(word[0])) {
                current = root->children[word[0]];
            }
            else {
                root->children[word[0]] = new CharNode(root);
                current = root->children[word[0]];
            }

            // iterate through all the characters in the word
            // build the trie out
            // the last node "current" should be marked as "end of word"
            for (int i = 1; i < word.size(); i++) {
                
                // if next char already exists in trie
                if (current->children.count(word[i])) {
                    current = current->children[word[i]];
                }
                else {
                    current->children[word[i]] = new CharNode(current);

                    current = current->children[word[i]];
                }

            }

            current->end = true;
            current->word = word;
            
        }

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        // go through board and use trie during dfs to know if we are matching with an existing word
        // if a word is found, we can delete it from the trie (so we don't double count it) 
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (root->children.count(board[i][j])) {
                    // if this letter is first letter of some word
                    // CharNode *current = trie[board[i][j]];
                    dfs(i, j, board, visited, root->children[board[i][j]], board[i][j]);
                }
            }
        }

        // return vector<string>(found.begin(), found.end());
        return found;

    }

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    void dfs(int i, int j, vector<vector<char>>& board, vector<vector<bool>>& visited, CharNode *current, char c) {

        // end of word? then add word to found
        if (current->end) {
            found.push_back(current->word);
            // found.insert(current->word);
            current->end = false;

            // if no children, then return early
            // also delete this node from the parent node's children 
            // also can delete the node itself (free memory)
            if (current->children.empty()) {
                // how can we get the character ..? pass in as param maybe, or current->word.back()
                current->parent->children.erase(c);
                // delete current; // slows down program?
                return;
            }
            // otherwise this word could be a prefix of another word, so continue dfs
            
        }

        visited[i][j] = true;

        for (int k = 0; k < 4; k++) {
            int ii = i + di[k];
            int jj = j + dj[k];

            // cout << "k" << k << endl;

            // skip if out of bounds or visited or not a character in the trie
            if (ii < 0 || jj < 0 || ii >= n || jj >= m || visited[ii][jj] || current->children.count(board[ii][jj]) == 0) {
                continue;
            }
            // cout << "dfs" << endl;
            dfs(ii, jj, board, visited, current->children[board[ii][jj]], board[ii][jj]);

        }

        visited[i][j] = false;

        // after 4 direction dfs, if current node has no children, we can delete it from parent
        if (current->children.empty()) {
            // how can we get the character ..? pass in as param maybe, or current->word.back()
            current->parent->children.erase(c);
            // delete current; // slows down program?
            return;
        }

    }
};

/*
struct CharNode {
    map<char, CharNode *> children;
    bool end = false;
    string word; // only exists if is end of word; for quick access
};

class Solution {
public:
    CharNode *root;
    // map<char, CharNode *> trie;
    vector<string> found;
    // set<string> found;
    int n, m;

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        // new attempt: don't worry about deleting the word from the trie

        n = board.size();
        m = board[0].size();

        // found = 0;

        // create trie 
        root = new CharNode();
        // trie --> root->children
        
        for (string& word : words) {

            CharNode *current = nullptr;
            // find the first char in the map
            if (root->children.count(word[0])) {
                current = root->children[word[0]];
            }
            else {
                root->children[word[0]] = new CharNode();
                current = root->children[word[0]];
            }

            // iterate through all the characters in the word
            // build the trie out
            // the last node "current" should be marked as "end of word"
            for (int i = 1; i < word.size(); i++) {
                
                // if next char already exists in trie
                if (current->children.count(word[i])) {
                    current = current->children[word[i]];
                }
                else {
                    current->children[word[i]] = new CharNode();

                    current = current->children[word[i]];
                }

            }

            current->end = true;
            current->word = word;
            
        }

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        // go through board and use trie during dfs to know if we are matching with an existing word
        // if a word is found, we can delete it from the trie (so we don't double count it) 
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (root->children.count(board[i][j])) {
                    // if this letter is first letter of some word
                    // CharNode *current = trie[board[i][j]];
                    dfs(i, j, board, visited, root->children[board[i][j]]);
                }
            }
        }

        // return vector<string>(found.begin(), found.end());
        return found;

    }

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    void dfs(int i, int j, vector<vector<char>>& board, vector<vector<bool>>& visited, CharNode *current) {

        // end of word? then add word to found
        if (current->end) {
            found.push_back(current->word);
            // found.insert(current->word);
            current->end = false;

            // if no children, then delete the word from the trie, and return early
            if (current->children.empty()) {
                return;
            }
            // otherwise this word could be a prefix of another word, so continue dfs
            
        }

        visited[i][j] = true;

        for (int k = 0; k < 4; k++) {
            int ii = i + di[k];
            int jj = j + dj[k];

            // cout << "k" << k << endl;

            // skip if out of bounds or visited or not a character in the trie
            if (ii < 0 || jj < 0 || ii >= n || jj >= m || visited[ii][jj] || current->children.count(board[ii][jj]) == 0) {
                continue;
            }
            // cout << "dfs" << endl;
            dfs(ii, jj, board, visited, current->children[board[ii][jj]]);

        }

        visited[i][j] = false;

    }
};
*/







/*
struct CharNode {
    map<char, CharNode *> nextChars;
    bool isEndOfWord = false;
    string word; // only exists if is end of word; for quick access
    CharNode *parent = nullptr;
    CharNode(CharNode *parent) : parent(parent) {}
};

class Solution {
public:
    CharNode *root;
    // map<char, CharNode *> trie;
    vector<string> found;
    int n, m;

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        n = board.size();
        m = board[0].size();

        // found = 0;

        // create trie 
        root = new CharNode(nullptr);
        // trie --> root->nextChars
        
        for (string& word : words) {

            CharNode *current = nullptr;
            // find the first char in the map
            if (root->nextChars.count(word[0])) {
                current = root->nextChars[word[0]];
            }
            else {
                root->nextChars[word[0]] = new CharNode(root); // parent is the root node
                current = root->nextChars[word[0]];
            }

            // iterate through all the characters in the word
            // build the trie out
            // the last node "current" should be marked as "end of word"
            for (int i = 1; i < word.size(); i++) {
                
                // if next char already exists in trie
                if (current->nextChars.count(word[i])) {
                    current = current->nextChars[word[i]];
                }
                else {
                    current->nextChars[word[i]] = new CharNode(current); // set current to parent of this new char node

                    current = current->nextChars[word[i]];
                }

            }

            current->isEndOfWord = true;
            current->word = word;
            
        }

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        // go through board and use trie during dfs to know if we are matching with an existing word
        // if a word is found, we can delete it from the trie (so we don't double count it) 
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (root->nextChars.size() == 0) return found; // return early trie is now empty
                if (root->nextChars.count(board[i][j])) {
                    // if this letter is first letter of some word
                    // CharNode *current = trie[board[i][j]];
                    dfs(i, j, board, visited, root->nextChars[board[i][j]]);
                }
            }
        }

        return found;


    }

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    void dfs(int i, int j, vector<vector<char>>& board, vector<vector<bool>>& visited, CharNode *current) {

        // end of word? then increase count and delete this word from the trie
        if (current->isEndOfWord) {
            // cout << "test" << endl;
            // found++;
            found.push_back(current->word);
            current->isEndOfWord = false;

            // if no children, then delete the word from the trie, and return early
            if (current->nextChars.empty()) {

                // while current has no children and is not the end of a word, temp = current, current = get parent, delete temp
                while (current != nullptr && current->nextChars.empty() && !current->isEndOfWord) {
                    CharNode *temp = current;
                    current = current->parent;
                    if (temp == root) {
                        // do not delete root, just return...? 
                    }
                    delete temp;
                    // also need to remove temp from parents' nextChars
                    if (parent != nullptr)
                }

                return;
            }
            // otherwise this word could be a prefix of another word, so continue dfs

            
        }

        visited[i][j] = true;

        for (int k = 0; k < 4; k++) {
            int ii = i + di[k];
            int jj = j + dj[k];

            // cout << "k" << k << endl;

            // how do i check if current points to a deallocated memory address?
            if (current ... )

            // skip if out of bounds or visited or not a character in the trie
            if (ii < 0 || jj < 0 || ii >= n || jj >= m || visited[ii][jj] || current->nextChars.count(board[ii][jj]) == 0) {
                continue;
            }
            // cout << "dfs" << endl;
            dfs(ii, jj, board, visited, current->nextChars[board[ii][jj]]);

        }

        visited[i][j] = false;

    }
};
*/