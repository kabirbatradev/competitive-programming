class Solution {
public:
    vector<string> letterCombinations(string digits) {

        vector<string> combinations;

        unordered_map<char, string> digit_to_letters = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };

        for (char digit : digits) {

            if (combinations.empty()) {
                combinations.push_back("");
            }

            // // digit to letter
            // int num = digit - '2'; // 2 -> 0, 3 -> 1
            
            // // first letter corresponding to that number
            // char letter = num*3 + 'a'; 

            vector<string> newCombinations;
            for (string combo : combinations) {
                // for (int i = 0; i < 3; i++) {
                //     string newCombo(combo);
                //     newCombo.push_back(letter + i);
                //     newCombinations.push_back(newCombo);
                // }
                for (char letter : digit_to_letters[digit]) {
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