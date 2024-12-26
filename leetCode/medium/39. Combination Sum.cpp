class Solution {
public:
    vector<vector<int>> combos;
    vector<int> currentCombo;
    int targetSum;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

        sort(candidates.begin(), candidates.end());

        targetSum = target;
        backtrack(0, 0, candidates);

        return combos;
    }

    void backtrack(int candidateIndex, int sum, vector<int>& candidates) {
        if (sum == targetSum) { // we have a combo
            combos.push_back(currentCombo);
            return;
        }
        if (sum > targetSum) return; // overshoot

        for (int i = candidateIndex; i < candidates.size(); i++) { // consider all candidates inclusive
            currentCombo.push_back(candidates[i]); // add used candidate to combo
            backtrack(i, sum + candidates[i], candidates); // add used candidate to the sum as well
            currentCombo.pop_back(); // remove from combo for other cases
        }

    }
};