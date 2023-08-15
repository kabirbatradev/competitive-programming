class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {

        // potential optimization:
        // store words in map (word -> count)
        // then, when the word is found, increment count by that word's count
        unordered_map<string, int> wordMap;
        for (string word : words) {
            if (wordMap.count(word) == 0) {
                wordMap.insert({word, 1});
            }
            else {
                wordMap[word]++;
            }
        }

        // create catalog (map) of every letter in s and its indeces
        unordered_map<char, vector<int>> m;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (m.count(c) == 0) {
                m.insert({c, {i}});
            }
            else {
                m[c].push_back(i);
            }
        }

        int count = 0;
        // for (string word : words) {
        for (pair<string, int> wordAndCount : wordMap) {
            string word = wordAndCount.first;

            int index = -1;
            bool fail = false;

            for (char c : word) {
                // cout << c << endl;
                // cout << m.count(c) << endl;
                // character not in string s
                if (m.count(c) == 0) {
                    // cout << "not found " << endl;
                    fail = true;
                    break;
                }

                // find smallest index larger than index 
                vector<int> indeces = m[c];
                // binary search
                int min = 0;
                int max = indeces.size() - 1;
                int best = -1;
                while (min <= max) {
                    int mid = (min + max) / 2;
                    if (indeces[mid] <= index) {
                        // too small so move up
                        // use <= because dont want to use the same character twice
                        min = mid + 1;
                    }
                    else {
                        // larger, so viable answer and move down
                        best = mid;
                        max = mid - 1;
                    }
                }
                if (best == -1) {
                    fail = true;
                    break;
                }

                // now that we have found an index for the character, update index 
                // next character must come after this index
                // cout << "index: " << best << endl;
                index = indeces[best];

            }
            if (!fail) {
                // count++;
                count += wordAndCount.second;
                // cout << word << " passed\n";
            }
        }

        return count;
        
    }
};