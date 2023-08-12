class Solution {
public:
    int maxProfit(vector<int>& prices) {

        // o(n^2) solution (brute force)

        int monies = 0;
        for (int i = 0; i < prices.size(); i++) {
            for (int j = i + 1; j < prices.size(); j++) {
                monies = max(prices[j] - prices[i], monies);
            }
        }

        return monies;
    }
};