class Solution {
public:
    bool doesAliceWin(string s) {

        // alice goes first, return true if alice

        // note that bob can remove no vowel = even number and just remove some character

        // there are a lot of characters so maybe we should try greedy instead of dp


        // what is the best move for alice?
        // if odd number of vowels, then take the entire string
        // if even number of vowels, then take the entire string up to (right before) the last vowel
            // bob cannot take anything because he would have to take the vowel?

        // does this mean alice always wins unless string has no vowels?

        
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        for (char c : s) {
            if (vowels.count(c) == 1) {
                // vowel found! alice wins
                return true;
            }
        }

        // no vowels
        return false;
        
    }
};