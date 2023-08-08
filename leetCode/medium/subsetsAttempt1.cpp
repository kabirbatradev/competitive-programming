// NOTE THIS IS NOT A WORKING SOLUTION
class Solution {
public:
    // vector<int> subsetsOfSizeN(vector<int>& nums, int n);

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        for (int subsetSize = 0; subsetSize <= nums.size(); subsetSize++) {
            vector<vector<int>> toInsert = subsetsOfSizeN(nums, subsetSize);
            ret.insert(ret.end(), toInsert.begin(), toInsert.end());
        }
        return ret;
    }

    // make a copy of the vector (no &)
    vector<vector<int>> subsetsOfSizeN(vector<int> nums, int n) {
        if (n == 0) {
            return {{}};
        }
        vector<vector<int>> ret;
        // for every number remaining, add it to the list 
        // but then remove it from remaining numbers to add...
        // i think i need to restart
        for (int i=0;i<nums.size();i++) {
            int X = nums.at(i);
            vector<int> numsWithoutX(nums);
            numsWithoutX.erase(numsWithoutX.begin() + i);
            vector<vector<int>> toInsert = subsetsOfSizeN(numsWithoutX, n-1);
            
            for (int j = 0; j < toInsert.size(); j++) {
                toInsert.at(j).push_back(X);
            }
            // return ret;
            ret.insert(ret.end(), toInsert.begin(), toInsert.end());
        }
        return ret;
    }
};