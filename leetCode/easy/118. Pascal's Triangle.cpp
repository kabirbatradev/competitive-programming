class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        vector<int> firstRow = {1};
        ret.push_back(firstRow);

        for (int i = 1; i < numRows; i++) {
            vector<int> prevRow = ret.back(); 

            ret.push_back(vector<int>(prevRow.size()+1));
            vector<int>& thisRow = ret.back(); 
            thisRow[0] = 1;
            thisRow.back() = 1;

            for (int j = 1; j < thisRow.size()-1; j++) {
                thisRow[j] = prevRow[j-1] + prevRow[j];
            }

        }

        return ret;
    }
};