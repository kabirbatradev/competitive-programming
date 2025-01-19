class Solution {
public:
    string foreignDictionary(vector<string>& words) {
        
        set<char> allLetters;
        map<char, int> inDegrees;
        map<char, vector<char>> adjList;

        // make sure allLetters has letters from first word
        for (char c : words[0]) {
            allLetters.insert(c);
        }

        for (int i = 1; i < words.size(); i++) {
            string& prev = words[i-1];
            string& curr = words[i];

            // update allLetters with any new letters
            for (char c : words[i]) {
                allLetters.insert(c);
            }
            
            int differingLetterIndex = -1;
            for (int j = 0; j < min(prev.length(), curr.length()); j++) {
                if (prev[j] != curr[j]) {
                    differingLetterIndex = j;
                    break;
                }
            }
            if (differingLetterIndex == -1) {
                // invalid case: prev = abcd, curr = abc
                if (prev.length() > curr.length()) {
                    return "";
                }
            }
            else {
                // add edge to the graph
                char a = prev[differingLetterIndex];
                char b = curr[differingLetterIndex];
                // allLetters.insert(a);
                // allLetters.insert(b);
                inDegrees[b]++;
                adjList[a].push_back(b);
            }
            
        }

        // get all chars with 0 indegree == not in inDegrees
        queue<char> q;
        for (char c : allLetters) {
            if (inDegrees.count(c) == 0) {
                q.push(c);
            }
        }

        string ret;
        while (!q.empty()) {
            char c = q.front();
            q.pop();

            ret.push_back(c);

            for (char adj : adjList[c]) {
                inDegrees[adj]--;
                if (inDegrees[adj] == 0) {
                    q.push(adj);
                    inDegrees.erase(adj); // remove from map so we can check for empty at the end
                }
            }
        }

        if (!inDegrees.empty()) return "";
        return ret;
        
    }
};

/*
compare neighboring strings
look for the letter that differs 

create edges and do topological sort
*/