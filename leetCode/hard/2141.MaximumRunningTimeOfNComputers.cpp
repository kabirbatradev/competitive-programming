class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {

        // goal: binary search the answer (consider a runtime)

        sort(batteries.begin(), batteries.end());

        long prefix[batteries.size()];
        prefix[0] = batteries.at(0);
        for (int i = 1; i < batteries.size(); i++) {
            prefix[i] = prefix[i-1] + batteries.at(i);
        }

        long min = prefix[0];
        long max = prefix[batteries.size()-1] / n; // divide by n since we are looking at runtimes for each computer

        long bestAnswer = -1;
        while (min <= max) {
            long mid = min + (max - min)/2;
            long considerRuntime = mid;

            if (checkPossible(n, batteries, prefix, considerRuntime)) {
                // try going higher
                min = mid + 1;
                bestAnswer = considerRuntime; // (mid)
            }
            else {
                // too high expectations
                max = mid - 1;
            }
            
        }
        
        return bestAnswer;

    }

    bool checkPossible(int n, vector<int>& batteries, long* prefix, long considerRuntime) {
        // find the index of the last battery still smaller than consider runtime
        // then use the prefix sum + remaining tructated batteries 
        // compare this sum to the considerRuntime to determine if it is possible

        int lastBatteryIndex = 0;
        if (batteries.at(batteries.size() - 1) < considerRuntime) {
            // skip the search for the last battery
            lastBatteryIndex = batteries.size() - 1;
        }
        else {
            // search for the last battery
            int start = 0;
            int end = batteries.size() - 1;
            while (start <= end) {
                int mid = start + (end - start)/2;
                if (batteries.at(mid) <= considerRuntime) {
                    start = mid + 1;
                    lastBatteryIndex = mid;
                }
                else {
                    // battery is larger than runtime
                    end = mid - 1;
                }
            }
        }

        long batteryHoursSum = prefix[lastBatteryIndex] // use all of the smaller batteries
            + (batteries.size() - 1 - lastBatteryIndex) * considerRuntime; 
            // use all of the larger batteries but truncated
        
        if (batteryHoursSum / n >= considerRuntime) {
            // if we have enough hours for each computer to hit the runtime requested
            return true;
        }
        return false;
    }
};