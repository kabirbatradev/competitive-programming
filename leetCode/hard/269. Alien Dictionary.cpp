class Solution {
public:
    /**
     * @param words: a list of words
     * @return: a string which is correct order
     */
    string alienOrder(vector<string> &words) {

        vector<set<int>> adjacencyList(26, set<int>());

        vector<int> inDegree(26, 0);

        set<int> exist;
        for (string word : words) {
            for (char c : word) {
                exist.insert(c-'a');
            }
        }

        // for (int i : exist) {
        //     cout << (char)(i+'a') << endl;
        // }

        // cout << "here" << endl;

        for (int i = 0; i < words.size() - 1; i++) {
            // cout << i << endl;

            int shorterLength = min(words[i].length(), words[i+1].length());
            int d = -1; // differentCharacterIndex
            for (int j = 0; j < shorterLength; j++) {
                if (words[i][j] != words[i+1][j]) {
                    d = j;
                    break;
                }
            }

            // cout << "x" << endl;

            // one word is a prefix of other
            if (d == -1) {
                if (words[i].length() > words[i+1].length()) {
                    return "";
                }
                continue; // first is prefix of second; no edge created
            }

            // cout << "y" << endl;

            // words[i][d] --> words[i+1][d]
            // cout << d << endl;
            // cout << words[i][d] - 'a' << endl;
            // cout << words[i] << endl;
            // cout << words[i+1][d] - 'a' << endl;
            // cout << words[i+1] << endl;

            int start = words[i][d] - 'a';
            int end = words[i+1][d] - 'a';

            // only increase indegree if not already in adjacency set
            if (adjacencyList[start].count(end) == 1) continue;
            adjacencyList[start].insert(end);
            inDegree[end]++;

            
            
        }

        // cout << "here" << endl;

        string out = "";

        // init pq
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < 26; i++) {
            if (inDegree[i] == 0) {
                pq.push(i);
            }
        }

        while (!pq.empty()) {
            int node = pq.top(); pq.pop();
            // cout << (node + 'a');
            if (exist.count(node) == 0) continue;
            out += (node + 'a');

            for (int end : adjacencyList[node]) {
                inDegree[end]--;
                if (inDegree[end] == 0) {
                    pq.push(end);
                }
            }
            
        }

        // cout << "here" << endl;
        

        // check for cycle
        for (int i = 0; i < 26; i++) {
            if (inDegree[i] != 0) {
                cout << "there is a cycle" << endl;
                cout << out << endl;
                return "";
            }
        }

        return out;
        
    }
};