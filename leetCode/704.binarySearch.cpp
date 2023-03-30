class Solution {
public:
    int search(vector<int>& nums, int target) {
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
        
        int min = 0;
        int max = nums.size() - 1;
        while (max >= min) {
            int middle = (max + min) / 2;

            if (nums.at(middle) == target) {
                return middle;
            }
            else if (target > nums.at(middle)) {
                min = middle + 1;
            }
            else {
                max = middle - 1;
            }
        }
        return -1;
    }

    
};