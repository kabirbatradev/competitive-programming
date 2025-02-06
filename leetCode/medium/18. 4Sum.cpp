class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // using t4 = tuple<int, int, int, int>;
        using ll = long long;
        int n = nums.size();

        sort(nums.begin(), nums.end());

        set<vector<int>> answers;

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                ll sum = nums[i] + nums[j];
                ll newTarget = target - sum;

                // two pointers:
                int a = 0;
                int b = n-1;
                while (a < b) {
                    // skip a or b are i or j
                    if (i == a || j == a) {
                        a++;
                        continue;
                    }
                    if (i == b || j == b) {
                        b--;
                        continue;
                    }

                    ll sum2 = nums[a] + nums[b];
                    if (sum2 == newTarget) {
                        // insert potential answer
                        vector<int> potentialAnswer = {
                            nums[i], nums[j], nums[a], nums[b]};
                        sort(potentialAnswer.begin(), potentialAnswer.end());
                        answers.insert(potentialAnswer);
                        a++; b--;
                        // a++;
                    }
                    else if (sum2 > newTarget) {
                        // sum too big, so push down the right pointer
                        b--;
                    }
                    else {
                        // sum too small, so move up the left pointer
                        a++;
                    }
                }
            }
        }

        vector<vector<int>> ret;
        for (vector<int> v : answers) {
            ret.push_back(v);
        }
        return ret;
        
    }
};

/*
2 sum sorted approach
sort array
double for loop to get all pairs
identify current target 
2 pointers to find 2 numbers that hit target 
(skip if any indices match current pair)
add to a list

get rid of duplicate values with the set of answers --> vector approach

*/

/*
hash table approach
key = sum of 2 values
value = list of pairs of indices that sum to that key

generate hash using double for loop: n choose 2 combinations

then double for loop (also n choose 2)
    find target - sum in the hash
    make sure no conflicting indices
    add to the set of sorted lists of answers

convert set into vector at the end

code:
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // using t4 = tuple<int, int, int, int>;
        int n = nums.size();

        // unordered_set<vector<int>> answers; // should handle duplicates for us
        set<vector<int>> answers; // should handle duplicates for us
        // return {};
        unordered_map<int, vector<pair<int, int>>> table;

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                int sum = nums[i] + nums[j];
                table[sum].push_back(make_pair(i, j));
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                int sum = nums[i] + nums[j];
                int newTarget = target - sum;
                if (table[newTarget].size() != 0) {
                    for (auto [a, b] : table[newTarget]) {
                        if (i == a || i == b || j == a || j == b) continue;
                        vector<int> potentialAnswer = {
                            nums[i], nums[j], nums[a], nums[b]};
                        sort(potentialAnswer.begin(), potentialAnswer.end());
                        answers.insert(potentialAnswer);
                    }
                }
            }
        }

        vector<vector<int>> ret;
        for (vector<int> v : answers) {
            ret.push_back(v);
        }
        return ret;
        
    }
};
*/