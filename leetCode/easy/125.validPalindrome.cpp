class Solution {
public:
    bool isPalindrome(string s) {
        if (s.length() <= 1) return true;

        int ptr1 = 0;
        int ptr2 = s.length()-1;

        while (ptr1 < ptr2) {
            if (!isalnum(s[ptr1])) {
                ptr1++;
                continue;
            }
            if (!isalnum(s[ptr2])) {
                ptr2--;
                continue;
            }

            if (tolower(s[ptr1]) != tolower(s[ptr2])) {
                return false;
            }
            ptr1++;
            ptr2--;
        }

        return true;
    }
};