class Solution {
public:
    vector<vector<int>> solution;
    int N;
    vector<vector<int>> combine(int n, int k) {
        solution = vector<vector<int>>();
        N = n;
        
        int remainingChoices = k;
        vector<int> path = vector<int>();
        traverse(path, 1, remainingChoices);

        return solution;
    }

    void traverse(vector<int>& path, int nStartIndex, int remainingChoices) {
        if (remainingChoices == 0) {
            solution.push_back(path);
            return;
        }

        for (int i = nStartIndex; i <= N; i++) {
            path.push_back(i);
            traverse(path, i+1, remainingChoices - 1); 
            // next traverse should start from after the element added to the path
            // decrement remaining choices
            path.pop_back();

        }
    }
};