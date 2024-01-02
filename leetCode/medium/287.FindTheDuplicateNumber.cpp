class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        int t = 0;
        int h = 0;
        while(true) {
            t = nums[t];
            h = nums[nums[h]];
            if (t == h) break;
        }
        int t2 = 0;
        while(true) {
            t = nums[t];
            t2 = nums[t2];
            if (t == t2) break;
        }
        return t2;
        
    }
};