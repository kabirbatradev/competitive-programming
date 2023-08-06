class Solution {
public:
    vector<string> letterCombinations(string digits) {

        // empty string edge case
        if (digits.length() == 0) {
            return vector<string>();
        }

        vector<string> combinations;

        // unordered_map<char, string> digit_to_letters = {
        //     {'2', "abc"},
        //     {'3', "def"},
        //     {'4', "ghi"},
        //     {'5', "jkl"},
        //     {'6', "mno"},
        //     {'7', "pqrs"},
        //     {'8', "tuv"},
        //     {'9', "wxyz"}
        // };

        // arrays should be faster than hashmap
        string digit_to_letters[] = {
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz",
        };
    
        // given at least 1 digit, start with empty string
        combinations.push_back("");

        // for every digit, update the list of combinations
        for (char digit : digits) {
            
            // replace combinations with new longer combinations
            vector<string> newCombinations;
            for (string combo : combinations) {
                // for each old combo, add 3 or 4 new combos

                // - '2' to offset for array ('2' -> 0 index)
                for (char letter : digit_to_letters[digit - '2']) {
                    string newCombo(combo);
                    newCombo.push_back(letter);
                    newCombinations.push_back(newCombo);
                }
                
            }
            combinations = newCombinations;
            
        }

        return combinations;
    }

};