class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> newList;
        newList.reserve(intervals.size()+1);

        bool inserted = false;

        for (int i = 0; i < intervals.size(); i++) {
            vector<int> current = intervals[i];

            if (inserted) {
                newList.push_back(current);
                continue;
            }

            // if current has passed the newInterval entirely, then we should insert
            if (current[0] > newInterval[1]) {
                newList.push_back(newInterval);
                newList.push_back(current);
                inserted = true;
                continue;
            }

            bool overlap = false;

            // overlaps the front of newInterval
            if (current[0] <= newInterval[0] && current[1] >= newInterval[0]) {
                newInterval[0] = current[0];
                overlap = true;
            }
            // overlaps the back of newInterval
            if (current[1] >= newInterval[1] && current[0] <= newInterval[1]) {
                newInterval[1] = current[1];
                overlap = true;
            }
            // current is within newInterval
            if (newInterval[0] <= current[0] && current[1] <= newInterval[1]) {
                overlap = true;
            }

            if (!overlap) {
                newList.push_back(current);
            }


        }

        if (!inserted) {
            newList.push_back(newInterval);
        }

        return newList;
        
    }
};





/*
        // identify the interval directly before new interval (including overlap)
        // check if overlap with prev
        // check if overlap with next
            // also check if overlap with multiple on the right?
        
        int mergeLeftIndex = -1;
        int mergeRightIndex = -1;

        
        if (newInterval[0] < intervals[0][0]) {
            // .... there is no interval that starts before
        }
        else {
            // use binary search
            int l = 0;
            int r = intervals.size()-1;
            while (l < r) {
                int midpoint = (l + r) / 2;
                if (intervals[midpoint][0] > newInterval[0]) {
                    r = midpoint - 1;
                }
                else {
                    l = midpoint + 1;
                }
            }
            // the left pointer will be the interval directly before the new interval

            // merge with left (only here where it exists)
            if (intervals[l][1] >= newInterval[0]) {
                mergeLeftIndex = l;
            }
        }

        // merge with right (if exists, can be multiple)
        // can binary search for interval that ends after (guarantees that later intervals do not overlap)
        // check if an "interval that ends after" exists
        if (intervals[intervals.size()-1][1] <= newInterval[1]) {
            // no interval ends after, so merge with all right intervals
        }
        else {
            // use binary search
            int l = 0;
            int r = intervals.size()-1;
            while (l < r) {
                int midpoint = (l + r) / 2;
                if (intervals[midpoint][0] > newInterval[0]) {
                    r = midpoint - 1;
                }
                else {
                    l = midpoint + 1;
                }
            }
            // the left pointer will be the interval directly before the new interval
        }
*/