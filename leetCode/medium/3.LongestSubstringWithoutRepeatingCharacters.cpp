class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // sliding window, use set to keep track of letters in use
        // increase window size if new letter is not in set
        // if in use, remove from back of window until that char is no longer in use

        if (s.length() == 0) return 0;

        int best = 1;
        unordered_set<char> inUse;
        int windowStart = 0;
        // int windowEnd = 0; // inclusive 
        inUse.insert(s[0]);

        for (int i = 1; i < s.length(); i++) {
            char c = s[i];

            if (inUse.count(c)) {
                // remove from back of window
                while (true) {
                    if (s[windowStart] == c) {
                        windowStart++;
                        // inUse.erase(c);
                        break;
                    }
                    else {
                        inUse.erase(s[windowStart]);
                        windowStart++;
                    }
                }
                continue; // no chance that this window is best, so just remove the "erase"
            }

            // insert into set
            inUse.insert(c);
            // windowEnd++;
            best = max(best, (int)inUse.size());

        }

        return best;
    }
};