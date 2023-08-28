class Compare {
public:
    bool operator()(const vector<int> first, const vector<int> second) const {
        return first[0] < second[0];
    }
};

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> finalIntervals;

        sort(intervals.begin(), intervals.end(), Compare());

        int greatestVal = -1;
        for (int i = 0; i < intervals.size(); i++) {

            vector<int> currentInterval = intervals[i];
            // cout << currentInterval[0] << endl;

            // if this interval is entirely after all prev, then no merge
            if (currentInterval[0] > greatestVal) {
                finalIntervals.push_back(currentInterval);
                greatestVal = currentInterval[1];
                continue;
            }
            greatestVal = max(greatestVal, currentInterval[1]);

            // vector<vector<int>> overlappingIntervals;
            int minimum = currentInterval[0];
            int maximum = currentInterval[1];
            // for (vector<int> prevInterval : finalIntervals) {
            
            int index = 0;
            while (index < finalIntervals.size()) {

                vector<int> prevInterval = finalIntervals[index];

                if (overlap(prevInterval, currentInterval)) {
                    // remove interval from final intervals
                    // update min max
                    finalIntervals.erase(finalIntervals.begin() + index);

                    minimum = min(prevInterval[0], minimum);
                    maximum = max(prevInterval[1], maximum);
                }
                else {
                    index++;
                }

            }

            finalIntervals.push_back({minimum, maximum});

        }

        return finalIntervals;
    }

    bool overlap(vector<int> first, vector<int> second) {
        return first[0] <= second[0] && first[1] >= second[0]
            || second[0] <= first[0] && second[1] >= first[0];
    }
};