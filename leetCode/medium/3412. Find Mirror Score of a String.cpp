class Solution {
public:
    long long calculateScore(string s) {

        long long score = 0;

        // stack for every unmarked letter (stack value is index)
        stack<int> unmarked[26];

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            char mirrorChar = 25 - (c - 'a') + 'a';
            if (unmarked[mirrorChar - 'a'].empty()) {
                // it has no mirror, so push onto stack
                unmarked[c - 'a'].push(i);
                
            }
            else {
                int j = unmarked[mirrorChar - 'a'].top();
                unmarked[mirrorChar - 'a'].pop();
                score += i - j;
            }
        }

        return score;
        
    }
};