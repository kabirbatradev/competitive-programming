class Compare {
    public:
    bool operator()(const vector<int>& first, const vector<int>& second) const {
        return first[0] < second[0];
    }
};

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // vector<vector<int>> finalIntervals;
        set<vector<int>, Compare> finalIntervals;

        // for (int i = 0; i < intervals.size(); i++) {
        //     vector<int> currentInterval = intervals[i];
        //     finalIntervals.insert(currentInterval);
        // }

        // for (auto it = finalIntervals.begin(); it != finalIntervals.end(); it++) {
        //     vector<int> interval = *it;
        //     cout << interval[0] << " " << interval[1] << endl;
        // }

        // return {};

        for (int i = 0; i < intervals.size(); i++) {

            vector<int> currentInterval = intervals[i];

            // vector<vector<int>> overlappingIntervals;
            int minimum = currentInterval[0];
            int maximum = currentInterval[1];
            // for (vector<int> prevInterval : finalIntervals) {
            
            auto it = finalIntervals.begin();
            // int index = 0;
            // for (auto it = finalIntervals.begin(); it != finalIntervals.end(); it++) {
            // while (index < finalIntervals.size()) {
            while (it != finalIntervals.end()) {

                // vector<int> prevInterval = finalIntervals[index];
                vector<int> prevInterval = *it;

                if (overlap(prevInterval, currentInterval)) {
                    // remove interval from final intervals
                    // update min max

                    // finalIntervals.erase(finalIntervals.begin() + index);
                    it = finalIntervals.erase(it);

                    minimum = min(prevInterval[0], minimum);
                    maximum = max(prevInterval[1], maximum);
                }
                else {
                    it++;
                }

                if (prevInterval[0] > currentInterval[1]) break;
                // break out of the loop early if prev intervals are entirely after the current

            }

            // finalIntervals.push_back({minimum, maximum});
            finalIntervals.insert({minimum, maximum});

        }

        // return finalIntervals;

        vector<vector<int>> finalIntervalsVector 
            = vector<vector<int>>(finalIntervals.begin(), finalIntervals.end());
        return finalIntervalsVector;
    }

    bool overlap(vector<int>& first, vector<int>& second) {
        return first[0] <= second[0] && first[1] >= second[0]
            || second[0] <= first[0] && second[1] >= first[0];
    }
};