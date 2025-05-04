class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        
        // first, group equivalent dominos:
        // then for every group larger than 2, 
        // # pairs = n choose 2 (number of ways to choose 2)
        // alternative calculation:
        // for every new duplicate, add the count of preexisting
        // this is the number of new pairs created

        int total = 0;

        // map<pair<int,int>, int> counter;
        // faster counter: just a vector, input is a 2 digit number
        vector<int> counter(100, 0); // max domino num is 99
        for (auto pair : dominoes) {
            int a = pair[0];
            int b = pair[1];
            if (a > b) swap(a, b);
            // i want a to be smaller
            // total += counter[{a, b}];
            // counter[{a, b}]++;

            total += counter[10*a + b]++;
            
        }
        return total;
    }
};