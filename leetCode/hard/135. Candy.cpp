class Solution {
public:
    int candy(vector<int>& ratings) {
        int total = 0;

        int currentHeight = 1;
        total++; // for first rating

        int decreasingChain = 1;

        stack<int> s;

        for (int i = 1; i < ratings.size(); i++) {
            int slope = ratings[i] - ratings[i-1];
            if (slope > 0) {
                currentHeight++;
                total += currentHeight;
                decreasingChain=1;
                s = stack<int>(); // clear stack because no longer decreasing
            }
            else if (slope == 0) {
                // repeated number; can reset to 1
                currentHeight = 1;
                total++;
                decreasingChain=1;
                s = stack<int>(); // clear stack
            }
            else {

                // if current height is alr 1, then we have a decreasing chain
                if (currentHeight == 1) {
                    // decreasingChain++;
                    // handled below
                }
                else {
                    // otherwise push to stack
                    // height is 1
                    // chain length is 1
                    s.push(currentHeight);
                    currentHeight = 1;
                    decreasingChain = 1;

                    total += decreasingChain;
                    continue;
                }



                // currentHeight = 1; // current height still 1


                decreasingChain++;

                if (!s.empty()) {
                    // if stack has a height that needs to be pushed up by current decreasing chain
                    if (s.top() == decreasingChain) {
                        s.pop();
                        decreasingChain++;
                    }
                }
                else {
                    // stack is empty, so nothing to worry about
                }

                total += decreasingChain;
            }
        }

        return total;
    }
};