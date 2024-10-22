class Solution {
public:
    int maximumSwap(int num) {

        string numString = to_string(num);

        int bestSwapX = -1;
        int bestSwapY = -1;

        char maxSoFar = -1;
        int maxIndex = -1;
        
        // keep track of max from the right
        // if num is smaller than max, then thats the best swap so far

        for (int i = numString.length()-1; i >= 0; i--) {
            char c = numString[i];
            if (c > maxSoFar) {
                maxSoFar = c;
                maxIndex = i;
            }
            else if (c < maxSoFar) {
                bestSwapX = i;
                bestSwapY = maxIndex;
            }
        }

        if (bestSwapX == -1) return num;
        swap(numString[bestSwapX], numString[bestSwapY]);
        return stoi(numString);
    }
};