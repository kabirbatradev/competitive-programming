class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        unordered_set<int> seen(nums.begin(), nums.end());
        // for (int num : nums) {
        //     seen.insert(num);
        // }
        int i = 1;
        while (seen.find(i) != seen.end()) {
            // if (seen.find(i) == seen.end()) {
            //     // cout << i << "\n";
            //     return i;
            // }
            i++;
        }
        return i;
        
    }
};

// class Solution {
// public:
//     int firstMissingPositive(vector<int>& nums) {
//         unordered_set<int> seen;
//         for (int num : nums) {
//             seen.insert(num);
//         }
//         int i = 1;
//         while (true) {
//             if (seen.find(i) == seen.end()) {
//                 // cout << i << "\n";
//                 return i;
//             }
//             i++;
//         }
        
//     }
// };