class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            seen.insert(num);
        }
        int i = 1;
        while (true) {
            if (seen.find(i) == seen.end()) {
                // cout << i << "\n";
                return i;
            }
            i++;
        }
        
    }
};