class Solution {
public:
    vector<vector<int>> solution;
    vector<vector<int>> combine(int n, int k) {
        solution = vector<vector<int>>();
        
        int remainingChoices = k;
        traverse(vector<int>(), n, 1, remainingChoices);

        return solution;
    }

    void traverse(vector<int> path, int n, int nStartIndex, int remainingChoices) {
        if (remainingChoices == 0) {
            solution.push_back(path);
            return;
        }

        for (int i = nStartIndex; i <= n; i++) {
            path.push_back(i);
            traverse(path, n, i+1, remainingChoices - 1); 
            // next traverse should start from after the element added to the path
            // decrement remaining choices
            path.pop_back();

        }
    }
};