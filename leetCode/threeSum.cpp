class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        // unordered_set<vector<int>> solutionsSet;
        set<vector<int>> solutionsSet;

        sort(nums.begin(), nums.end());

        // let nums[i] be the third number
        for (int i = 0; i < nums.size(); i++) {
            // skip when nums[i] is the same as the previous
            if (i != 0 && nums.at(i) == nums.at(i-1)) continue;
            int target = 0 - nums.at(i);
            cout << "target: " << target << endl;

            // now do 2 pointers (left and right)
            int left = 0;
            int right = nums.size() - 1;

            while (left < right) {

                // cout << "   left: " << left << " " << nums.at(left) << endl;
                // cout << "   right: " << right << " " << nums.at(right) << endl;
                // cout << "      sum: " << nums.at(left) + nums.at(right) << endl;

                // stop when left and right have met in the middle
                // if (left == right) {
                //     break;
                // }

                // skip if left == i or right == i
                if (left == i) {
                    left++;
                    continue;
                }
                if (right == i) {
                    right--;
                    continue;
                }

                if (nums.at(left) + nums.at(right) == target) {
                    vector<int> potentialNewSolution = {nums.at(i), nums.at(left), nums.at(right)};
                    // sort it so the set can eliminate duplicates
                    sort(potentialNewSolution.begin(), potentialNewSolution.end());
                    solutionsSet.insert(potentialNewSolution);
                    // dont break bc there could be more solutions
                    left++;
                    right--;
                }
                if (nums.at(left) + nums.at(right) < target) {
                    left++;
                }
                else if (nums.at(left) + nums.at(right) > target) {
                    right--;
                }
            }


        }
        
        vector<vector<int>> solutions;
        for (vector<int> triple : solutionsSet) {
            solutions.push_back(triple);
        }

        return solutions;
    }
};