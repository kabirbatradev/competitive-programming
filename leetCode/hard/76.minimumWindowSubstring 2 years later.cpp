class Solution {
public:
    string minWindow(string s, string t) {

        // histogram map representing chars in string t
        map<char, int> target;
        for (char c : t) {
            target[c]++;
        }
        int uniqueChars = target.size();

        unordered_map<char, int> window;
        int charsCompleted = 0; // once this is equal to # unique chars, we have a valid window
        // slinky sliding window that tries to keep minimum valid window
        int bestIndex = 0;
        int bestLength = INT_MAX;
        int l = 0; 
        int r = 0;
        while (true) {
            // cout << "current substring: " << s.substr(l, r-l) << endl;
            // if not valid, then increase size of window
            if (charsCompleted != uniqueChars) {
                if (r == s.size()) break; // not valid and want to grow further but out of space
                // when adding a new character, add it to window, 
                // and check if the count now matches the target?
                if (++window[s[r]] == target[s[r]]) {
                    charsCompleted++;

                    // might be valid now!
                    // lets elegantly do this check under this (instead of making it an else)
                    
                }
                // if it alr exceeded, then no need to increment count again
                r++;
            }


            // if its now valid, or was already valid, then 
            // first, update the best valid window
            // then remove from left end of window
            // and if we lost the required count, then we have to decrement chars completed
            if (charsCompleted == uniqueChars) {
                // new smallest length
                if (r - l < bestLength) {
                    bestLength = r - l;
                    bestIndex = l;
                    // cout << s.substr(bestIndex, bestLength) << endl;
                }
                // if we just lost the counts, we are no longer valid 
                if (--window[s[l]] + 1 == target[s[l]]) {
                    charsCompleted--; // no longer valid
                }
                l++;
            }
        }

        if (bestLength == INT_MAX) return "";
        return s.substr(bestIndex, bestLength);
    }
};