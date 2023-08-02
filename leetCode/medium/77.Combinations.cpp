class Solution {
public:
    vector<vector<int>> solution;
    vector<vector<int>> combine(int n, int k) {
        solution = vector<vector<int>>();
        
        queue<int> remainingChoicesList;
        for (int i = 1; i <= n; i++) remainingChoicesList.push(i);
        int remainingChoices = k;
        traverse(vector<int>(), remainingChoicesList, remainingChoices);

        return solution;
    }

    void traverse(vector<int> path, queue<int> remainingChoicesList, int remainingChoices) {
        if (remainingChoices == 0) {
            solution.push_back(path);
            return;
        }

        while (!remainingChoicesList.empty()) {
            int choice = remainingChoicesList.front(); // pops out smaller numbers first
            remainingChoicesList.pop();

            path.push_back(choice);
            traverse(path, remainingChoicesList, remainingChoices - 1); // decrement remaining choices
            path.pop_back();

        }
    }
};