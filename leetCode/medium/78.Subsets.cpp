class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> allSubsets;
        allSubsets.reserve(1 << nums.size());
        // allSubsets.reserve(pow(2, nums.size()));

        allSubsets.push_back(vector<int>());

        for (int i = 0; i < nums.size(); i++) {
            allSubsets.insert(allSubsets.end(), allSubsets.begin(), allSubsets.end());
            for (int j = 0; j < allSubsets.size()/2; j++) {
                allSubsets.at(j).push_back(nums.at(i));
            }
        }

        return allSubsets;
    }
};