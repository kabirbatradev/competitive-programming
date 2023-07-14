class Solution {
public:
    bool isAnagram(string s, string t) {
        // unordered_multiset<char> bean;

        if (s.length() != t.length()) return false;

        int bean2[26] = {0};

        for (int i = 0; i < s.length(); i++) {
            bean2[s[i] - 'a']++;
            bean2[t[i] - 'a']--;
        }

        for (int i = 0; i < 26; i++) {
            // cout << bean2[i] << endl;
            if (bean2[i] != 0) return false;
        }

        return true;

    }
};