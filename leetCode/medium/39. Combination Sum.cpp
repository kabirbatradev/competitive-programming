class Solution {
public:
    // is it faster when tables are a global varaible? no
    // vector<int> candidates;
    // vector<vector<vector<int>>> dp;
    // vector<bool> solved;


    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    // vector<vector<int>> combinationSum(vector<int>& candidatess, int target) {

        // candidates = candidatess;

        vector<vector<vector<int>>> dp(target+1); // at each sub target, you have an empty list of combations
        vector<bool> solved(target+1, false);
        // dp = vector<vector<vector<int>>>(target+1);
        // solved = vector<bool>(target+1, false);


        // zero case
        // should return a single empty combination (for all future combinations to build on)
        dp[0].push_back(vector<int>());
        solved[0] = true;

        return explore(target, candidates, dp, solved);
        // return explore(target);

    }

    vector<vector<int>> explore(int subTarget, vector<int>& candidates, vector<vector<vector<int>>>& dp, vector<bool>& solved) {
    // vector<vector<int>> explore(int subTarget) {
        // check in dp cache (handles zero case)
        if (solved[subTarget]) return dp[subTarget];

        vector<vector<int>> allCombinations;

        // consider every candidate, call explore() on previous position
        // go through every combination, 
        // only add the candidate to the end if its greater than the last candidate in the combination 
            // getting uniqueness from being sorted

        for (int can : candidates) {
            int pos = subTarget - can;
            if (pos < 0) continue;

            vector<vector<int>> combinations = explore(pos, candidates, dp, solved);
            // vector<vector<int>> combinations = explore(pos);

            for (vector<int>& combo : combinations) {
                // note special case: combo is empty bc pos = 0
                if (!combo.empty() && combo.back() > can) continue;
                combo.push_back(can);
                allCombinations.push_back(combo);
            }
            
        }

        // update the cache before returning
        solved[subTarget] = true;
        dp[subTarget] = allCombinations;

        return allCombinations;

    }
};


/*
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        // int dp[target+1] = {0};
        // vector<int> dp(target+1, 0);
        // dp[0] = 1;

        vector<vector<pair<int,int>>> dp(target+1);

        // at each position, store list of pairs: 
            // (prev target, candidate added to it (to get to current target))
        

        // zero case:
        for (int can : candidates) {
            int pos = 0 + can;
            if (pos > target) continue;
            dp[pos].push_back(make_pair(0, can));
        }

        for (int i = 1; i < target+1; i++) {

            // if is no way to get to this position, then skip
            if (dp[i].size() == 0) continue;

            // create new links forward using each candidate
            for (int can : candidates) {
                // for uniqueness, only use larger candidates ..? how do I implement this properly?
                int pos = i + can;
                if (pos > target) continue;
                dp[pos].push_back(make_pair(i, can));
            }
            
        }

        
        // dp[target] now has links back. follow the chain of links to build all the combinations
        return explore(target, dp, candidates);

        // return dp[target];
    }

    vector<vector<int>> explore(int target, vector<vector<pair<int,int>>>& dp, vector<int>& candidates) {
        vector<vector<int>> allCombinations;

        // base case: target = 0
            // should return a single empty combination (for all future combinations to build on)
        if (target == 0) {
            allCombinations.push_back(vector<int>());
            return allCombinations;
        }

        for (pair<int, int> p : dp[target]) {
            int prevTarget = p.first;
            int candidateUsed = p.second;

            vector<vector<int>> combinations = explore(prevTarget, dp, candidates);

            for (vector<int>& combo : combinations) {
                combo.push_back(candidateUsed);
                allCombinations.push_back(combo);
            }

        }

        return allCombinations;

    }
};
*/