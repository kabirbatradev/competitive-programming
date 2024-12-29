class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {

        // potential solution: create a map from number to all pairs that multiply to that num
        // This solution still TLE

        // indices in the pair are guaranteed to be at least 4 apart...

        unordered_map<int, vector<pair<int, int>>> m;

        for (int a = 0; a < nums.size(); a++) {
            for (int b = a+4; b < nums.size(); b++) {
                m[nums[a] * nums[b]].push_back(make_pair(a, b));
            }
        }

        long long ret = 0;
        for (auto [val, listOfPairs] : m) {
            // all list of pair indices multiply to the same value
            // we could sort them? maybe not needed, but could result in slightly faster code
            sort(listOfPairs.begin(), listOfPairs.end());
                // code would be faster if we took into account that if 
                // we want first.second=r > second.first=q
                // if second.first is larger, then the rest of the pairs are too large too
            // go through every pair of pairs (from the list of pairs) and if they meet the 
                // requirement of p < q < r < s, then increment ret
            for (int i = 0; i < listOfPairs.size(); i++) {
                for (int j = i+1; j < listOfPairs.size(); j++) {
                    auto [p, r] = listOfPairs[i];
                    auto [q, s] = listOfPairs[j];
                    if (q - p > 1 && r - q > 1 && s - r > 1) ret++;
                    if (!(r > q)) break;
                }
            }
        }
        

        // long long ret = 0;

        // // obviously TLE lol 545 / 557

        // for (int a = 0; a < nums.size(); a++) {
        //     for (int b = a+2; b < nums.size(); b++) {
        //         for (int c = b+2; c < nums.size(); c++) {
        //             for (int d = c+2; d < nums.size(); d++) {
        //                 // note the order
        //                 if (nums[a] * nums[c] == nums[b] * nums[d]) {
        //                     ret++;
        //                 }
        //                 // cout << a << " " << b << " " << c << " " << d << endl;
        //                 // cout << nums[a] * nums[b] << " " << nums[c] * nums[d] << endl;
        //             }
        //         }
        //     }
        // }

        return ret;

        
        
    }
};