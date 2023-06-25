class Solution {
public:
    string minWindow(string s, string t) {
        if (s.length() == 0 || t.length() == 0) return "";

        unordered_map<char, int> tMap;
        for (char c : t) {
            if (tMap.find(c) == tMap.end()) {
                tMap[c] = 1;
            }
            else {
                tMap[c]++;
            }
        }
        unordered_map<char, int> window; 
        for (auto& pair : tMap) {
            window[pair.first] = 0;
        }

        int bestLeft = 0; 
        int bestLength = s.length()+1; 
        bool found = false;
        
        int charactersCompleted = 0; 
        const int totalUniqueCharacters = tMap.size();

        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            char newChar = s[right];
            if (tMap.find(newChar) != tMap.end()) {
                window[newChar]++;
                if (window[newChar] == tMap[newChar]) {
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
            if (charactersCompleted != totalUniqueCharacters) continue;
            while (true) {
                char leftChar = s[left];
                if (tMap.find(leftChar) == tMap.end()) {
                    left++;
                    continue;
                }
                if (window[leftChar] > tMap[leftChar]) {
                    window[leftChar]--;
                    left++;
                }
                else {
                    found = true;
                    int substringLength = right+1 - left;
                    if (substringLength < bestLength) {
                        bestLeft = left;
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