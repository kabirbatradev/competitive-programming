class Solution {
public:
    int maxProfit(vector<int>& prices) {

        // o(n) solution

        int bestProfit = 0;
        int smallestNumSoFar = prices.at(0); // when to buy
        for (int i = 1; i < prices.size(); i++) {
            if (prices.at(i) < smallestNumSoFar) {
                // actually maybe buy here
                smallestNumSoFar = prices.at(i);
            }
            else {
                // sell here if prices.at(i) - smallestNumSoFar is bigger 
                bestProfit = max(bestProfit, prices.at(i) - smallestNumSoFar);
            }
        }
        return bestProfit;
    }
};