class Solution {
public:
    bool hasSameDigits(string s) {
        while (s.length() > 2) {
            for (int i = 0; i < s.size()-1; i++) {
                int a = s[i] - '0';
                int b = s[i+1] - '0';
                int c = (a + b) % 10;
                s[i] = (char)(c + '0');
            }
            s.pop_back(); // remove last char
        }
        return s[0] == s[1];
    }
};