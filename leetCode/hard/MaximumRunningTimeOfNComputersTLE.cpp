
// brute force solution

class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        // put all batteries into a pq
        priority_queue<int> pq; // max heap by default
        for (int charge : batteries) {
            pq.push(charge);
        }

        // while (!pq.empty()) {
        //     cout << pq.top() << " ";
        //     pq.pop();
        // }

        // while batteries remain in the pq, increment total minutes
        // break if not all computers can be satisfied
        long minutes = 0; 
        while (!pq.empty()) {
            bool outOfBatteries = false;
            vector<int> chargeOfCurrentlyUsingBatteries;
            for (int i = 0; i < n; i++) {
                if (pq.empty()) {
                    outOfBatteries = true;
                    break;
                }
                int remainingCharge = pq.top();
                pq.pop();

                if (remainingCharge - 1 != 0)
                    chargeOfCurrentlyUsingBatteries.push_back(remainingCharge-1);
            }
            if (outOfBatteries) break;
            
            minutes++;

            for (int charge : chargeOfCurrentlyUsingBatteries) {
                pq.push(charge);
            }

        }

        return minutes;
    }
};