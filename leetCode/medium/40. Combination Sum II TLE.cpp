class Solution {
public:
    int target;
    vector<pair<int, int>> candidatesCounts; // list of {candidate, count}

    // startIndex, currentSum --> list of combinations
    map<pair<int, int>, vector<vector<int>>> cache;

    vector<vector<int>> combinationSum2(vector<int>& candidates, int Target) {
        target = Target;
        // candidates = Candidates;

        map<int, int> candidateCountMap; 
        for (int c : candidates) {
            candidateCountMap[c]++; // should init to 0 automatically
        }
        for (auto pair : candidateCountMap) {
            candidatesCounts.push_back(pair);
            // cout << pair.first << " " << pair.second << endl;
        }
        // cout << endl;
        
        return dp(0, 0);
    }

    // returns list of combinations starting at index (inclusive) that sum to target given a start value (sum so far)
    vector<vector<int>> dp(int startIndex, int currentSum) {
        auto pair = make_pair(startIndex, currentSum);
        if (cache.count(pair)) {
            return cache[pair];
        }

        // base case: startIndex is candidates.size
        if (startIndex == candidatesCounts.size()) {
            if (currentSum == target) {
                cache[pair] = {{}};
                return {{}};
            }
            else {
                cache[pair] = {};
                return {};
            }
        }

        // try adding or not adding the current index, call dp with next index and new sum
        // for every combination in the list returned, add the current number to the start (or not if wasnt used)

        vector<vector<int>> ret;

        // cout << startIndex << " " << currentSum << endl;

        auto [candidate, count] = candidatesCounts[startIndex];
        // cout << candidate << " " << count << endl;
        // cout << endl;

        // note count should be inclusive
        for (int i = 0; i <= count; i++) { 
            // i is number of candidates we want to use 
            vector<vector<int>> combos = dp(startIndex+1, currentSum + candidate * i); // start with 0, each iteration adds more candidate
            
            for (vector<int> combo : combos) {
                // combo.insert(combo.begin(), candidate, i); // insert at the start, third param is how many we want to insert
                combo.insert(combo.begin(), i, candidate); // insert at the start, third param is how many we want to insert
                // didnt expect the order of params to be like this
                // if (i >= 1)
                    // combo.insert(combo.begin(), candidate, i); // insert at the start, third param is how many we want to insert
                    // combo.insert(combo.begin(), i, candidate); // insert at the start, third param is how many we want to insert
                ret.push_back(combo);
            }
            
        }

        // vector<vector<int>> a = dp(startIndex+1, currentSum + candidates[startIndex]);
        // vector<vector<int>> b = dp(startIndex+1, currentSum);

        // for (vector<int> combo : a) {
        //     combo.insert(combo.begin(), candidates[startIndex]); // insert at the start
        //     ret.push_back(combo);
        // }
        // for (vector<int> combo : b) {
        //     // no insert for b because it wasnt used
        //     // combo.insert(0, candidates[startIndex]); // insert at the start
        //     ret.push_back(combo);
        // }

        cache[pair] = ret;
        return ret;

    }
};