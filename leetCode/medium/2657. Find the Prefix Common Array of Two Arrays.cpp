class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {

        int n = A.size();

        // int count[n] = {0};
        vector<int> count(n+1, 0);

        vector<int> ret(n, 0);

        int currentCount = 0;

        for (int i = 0; i < n; i++) {
            // if (i > 0)
            //     ret[i] = ret[i-1];


            count[A[i]]++;
            count[B[i]]++;
            if (count[A[i]] == 2) {
                // ret[i]++;
                currentCount++;
            }
            if (A[i] != B[i]) {
                if (count[B[i]] == 2) 
                    // ret[i]++;
                    currentCount++;
            }

            ret[i] = currentCount;
        }    
        return ret;    
    }
};