class Solution {
public:
    string minWindow(string s, string t) {
        // return "";
        if (s.length() == 0 || t.length() == 0) return "";

        unordered_multiset<char> tSet;
        unordered_set<char> tSetUnique;
        for (char c : t) {
            tSet.insert(c);
            tSetUnique.insert(c);
        }
        unordered_multiset<char> window;

        int bestLeft = 0; 
        // int bestRight = s.length()-1;
        int bestLength = s.length()+1;
        bool found = false;
        
        int charactersCompleted = 0; 
        const int totalUniqueCharacters = tSetUnique.size();
        // const int totalUniqueCharacters = tSet.size() - tSet.bucket_count();

        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            char newChar = s[right];
            if (tSet.find(newChar) != tSet.end()) {
                // cout << "add newChar to window: " << newChar << "\n";
                window.insert(newChar);
                // cout << "window state: ";
                // for (char c : window) {
                //     cout << c << " ";
                // }
                // cout << "\n";
                if (window.count(newChar) == tSet.count(newChar)) {
                    charactersCompleted++;
                }
            }
            else {
                continue;
            }

            // if, by adding this character, we now have a 
            // potential solution, move the left pointer until 
            // right before we lose the solution, and then mark 
            // it as the solution
            // cout << "num: " << charactersCompleted << "\n";
            if (charactersCompleted != totalUniqueCharacters) continue;
            // cout << "here";
            while (true) {
                char leftChar = s[left];
                if (tSet.find(leftChar) == tSet.end()) {
                    left++;
                    continue;
                }
                if (window.count(leftChar) > tSet.count(leftChar)) {
                    // cout << leftChar << ": " << window.count(leftChar) << "\n";
                    // window.erase(leftChar); // ecda (e is the left)
                    window.erase(window.find(leftChar)); 
                    // problem was that erase deletes all occurrences :c
                    left++;
                }
                else {
                    found = true;
                    int substringLength = right+1 - left;
                    // cout << "found substring: " << s.substr(left, substringLength) << "\n";
                    if (substringLength < bestLength) {
                        bestLeft = left;
                        // bestRight = right;
                        bestLength = substringLength;
                        if (bestLength == t.length()) {
                            return s.substr(bestLeft, bestLength);
                        }
                    }
                    break;
                }
            }
            
        }
        if (!found) return "";
        return s.substr(bestLeft, bestLength);
    }
};