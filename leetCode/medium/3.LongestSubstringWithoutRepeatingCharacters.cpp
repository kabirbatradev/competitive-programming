class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        int longestLength = 0;
        unordered_set<char> windowLetters;

        int windowLeftIndex = 0;
        for (int i = 0; i < s.length(); i++) {

            if (windowLetters.find(s.at(i)) != windowLetters.end()) {
                // is in the set:

                // keep removing from the left side of the window 
                // until the new letter is removed
                bool done = false;
                while (!done) {
                    if (s.at(i) == s.at(windowLeftIndex)) {
                        done = true;
                    }
                    windowLetters.erase(s.at(windowLeftIndex));
                    windowLeftIndex++;
                }
            }

            // now it is guaranteed to not be in the set
            windowLetters.insert(s.at(i));

            // if new longest then update
            if (windowLetters.size() > longestLength) {
                longestLength = (int)windowLetters.size();
            }
        }

        return longestLength;
    }
};