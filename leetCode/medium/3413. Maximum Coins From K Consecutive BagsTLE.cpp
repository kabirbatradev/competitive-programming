class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        using ll = long long;

        // observation: subsequence will always start or end alongside an interval's start/end

        // idea: go through all intervals
        // consider starting at its start or ending at its end
        
        // for each interval:
        // go through all other intervals
        // if they fit in the current subsection, then add to the count
        // if partially fit, then only add partially

        
        // new idea:
        // sort all intervals (by start)
        // consider starting or ending at an interval
        // if theres more space, go in that direction in the list of sorted intervals
        sort(coins.begin(), coins.end());

        // what if a specific case is really slow?
            // if k is larger than the union of all intervals, then just add all coins
        if (k >= coins.back()[1] - coins.front()[0] + 1) {
            ll total = 0;
            for (vector<int>& interval : coins) {
                total += (ll)interval[2] * ((ll)interval[1] - (ll)interval[0] + 1);
            }
            return total;
        }
        // as we move onto the next interval, 
            // we could try to keep track of stuff? like dp? how could that be done though...

        long long best = 0;

        for (int i = 0; i < coins.size(); i++) {
            // consider left-aligned
            // vector<int> interval = coins[i]
            ll l = coins[i][0];
            ll r = coins[i][1];
            ll val = coins[i][2];
            
            ll start = coins[i][0];
            ll end = start + k - 1; // inclusive

            long long currentTotal = 0;

            // consider the current interval first
            // case 1: current interval ends before "end" --> add everything
            // case 2: interval ends after or right at "end" --> don't add all coins, continue early
            // case 1:
            if (coins[i][1] < end) {
                currentTotal = val * (r - l + 1);
            }
            // case 2:
            else {
                currentTotal = k * val;
                best = max(best, currentTotal);
                continue;
            }

            // now loop forward from current interval
            for (int j = i+1; j < coins.size(); j++) {
                // if (i == j) continue;

                l = coins[j][0];
                r = coins[j][1];
                val = coins[j][2];

                // check if this interval overlaps with [start, end]
                if (start <= r && end >= l) {
                    // how much overlap?
                    ll subStart = max(start, l);
                    ll subEnd = min(end, r);
                    currentTotal += val * (subEnd - subStart + 1);

                }
                // if subsection didnt fully overlap interval, 
                // then we can break loop early
                if (end < r) break;
            }

            // again, check if this is best
            best = max(best, currentTotal);
        }

        // in another loop, we can consider right-aligned
        for (int i = 0; i < coins.size(); i++) {
            // consider right-aligned
            // vector<int> interval = coins[i]
            ll l = coins[i][0];
            ll r = coins[i][1];
            ll val = coins[i][2];

            // int start = coins[i][0];
            // int end = start + k - 1; // inclusive
            ll end = r; // inclusive
            ll start = r - k + 1;

            long long currentTotal = 0;

            // consider the current interval first
            // case 1: current interval starts after "start" --> add everything
            // case 2: interval starts before or right at "start" --> don't add all coins, continue early
            // case 1:
            if (l > start) {
                currentTotal = val * (r - l + 1);
            }
            // case 2:
            else {
                currentTotal = k * val;
                best = max(best, currentTotal);
                continue;
            }

            // now loop through all other intervals
            // actually start at i-1 and go backward
            for (int j = i-1; j >= 0; j--) {
                // if (i == j) continue;

                l = coins[j][0];
                r = coins[j][1];
                val = coins[j][2];

                // check if this interval overlaps with [start, end]
                if (start <= r && end >= l) {
                    // how much overlap?
                    ll subStart = max(start, l);
                    ll subEnd = min(end, r);
                    currentTotal += val * (subEnd - subStart + 1);
                }
                // if no fully overlap, break early (start is after l)
                if (start > l) break;
            }

            // again, check if this is best
            best = max(best, currentTotal);
        }

        return best;



        /*
        long long best = 0;

        for (int i = 0; i < coins.size(); i++) {
            // consider left-aligned
            // vector<int> interval = coins[i]
            ll l = coins[i][0];
            ll r = coins[i][1];
            ll val = coins[i][2];
            
            ll start = coins[i][0];
            ll end = start + k - 1; // inclusive

            long long currentTotal = 0;

            // consider the current interval first
            // case 1: current interval ends before "end" --> add everything
            // case 2: interval ends after or right at "end" --> don't add all coins, continue early
            // case 1:
            if (coins[i][1] < end) {
                currentTotal = val * (r - l + 1);
            }
            // case 2:
            else {
                currentTotal = k * val;
                best = max(best, currentTotal);
                continue;
            }

            // now loop through all other intervals
            for (int j = 0; j < coins.size(); j++) {
                if (i == j) continue;

                l = coins[j][0];
                r = coins[j][1];
                val = coins[j][2];

                // check if this interval overlaps with [start, end]
                if (start <= r && end >= l) {
                    // how much overlap?
                    ll subStart = max(start, l);
                    ll subEnd = min(end, r);
                    currentTotal += val * (subEnd - subStart + 1);
                }
            }

            // again, check if this is best
            best = max(best, currentTotal);
        }

        // in another loop, we can consider right-aligned
        for (int i = 0; i < coins.size(); i++) {
            // consider right-aligned
            // vector<int> interval = coins[i]
            ll l = coins[i][0];
            ll r = coins[i][1];
            ll val = coins[i][2];

            // int start = coins[i][0];
            // int end = start + k - 1; // inclusive
            ll end = r; // inclusive
            ll start = r - k + 1;

            long long currentTotal = 0;

            // consider the current interval first
            // case 1: current interval starts after "start" --> add everything
            // case 2: interval starts before or right at "start" --> don't add all coins, continue early
            // case 1:
            if (l > start) {
                currentTotal = val * (r - l + 1);
            }
            // case 2:
            else {
                currentTotal = k * val;
                best = max(best, currentTotal);
                continue;
            }

            // now loop through all other intervals
            for (int j = 0; j < coins.size(); j++) {
                if (i == j) continue;

                l = coins[j][0];
                r = coins[j][1];
                val = coins[j][2];

                // check if this interval overlaps with [start, end]
                if (start <= r && end >= l) {
                    // how much overlap?
                    ll subStart = max(start, l);
                    ll subEnd = min(end, r);
                    currentTotal += val * (subEnd - subStart + 1);
                }
            }

            // again, check if this is best
            best = max(best, currentTotal);
        }

        return best;
        */
        
    }
};