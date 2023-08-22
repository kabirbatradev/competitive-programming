class Solution {
public:
    string convertToTitle(int columnNumber) {

        // this was a deceptively hard problem
        
        string ans;

        while (columnNumber != 0) {

            char c = (columnNumber-1) % 26 + 'A';

            ans.insert(0, string(1, c));

            columnNumber = (columnNumber - 1) / 26;

        }

        
        return ans;
        
    }
};