

class Solution {
public:
    vector<vector<int>> solutions;
    int n, k;
    vector<vector<int>> combine(int n, int k) {
        this->n = n;
        this->k = k;
        
        unordered_set<int>remainingNumsToAdd;
        for (int i = 0; i < n; i++) {
            remainingNumsToAdd.insert(i+1);
        }
        
        generateCombinations(vector<int>(), remainingNumsToAdd);
        
        return this->solutions;
    }
    
    // how to generate combinations (solutions)
    // we have n, we have k
    // n is the range 1, 2, 3 ... n
    // k is the size of the grouping
    // a group must be size k
    // if a group has k elements, add it to the solutions and stop recursing
    // if a group has less than k elements, 
        // then add an element from the remaining elements and decrease remaining elements needed
        // and also dont add it and dont decrease remaining elements needed.
    
    // remaining nums to add could be a set
    void generateCombinations(vector<int> buildingSolution, unordered_set<int> remainingNumsToAdd) {
        if (buildingSolution.size() == this->k) {
            this->solutions.push_back(buildingSolution);
            return;
        }
        if (remainingNumsToAdd.size() == 0) {
            return;
        }
        
        unordered_set<int> newRemaining(remainingNumsToAdd);
        int potentialElement = *newRemaining.begin();
        newRemaining.erase(newRemaining.begin());
        
        vector<int> newSolution1(buildingSolution);
        vector<int> newSolution2(buildingSolution);
        
        newSolution1.push_back(potentialElement);
        
        generateCombinations(newSolution1, newRemaining);
        generateCombinations(newSolution2, newRemaining);
        
    }
    
    
};