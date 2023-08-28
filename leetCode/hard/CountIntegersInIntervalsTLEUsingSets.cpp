class Compare {
public:
    bool operator()(const pair<int, int> first, const pair<int, int> second) const {
        return first.first < second.first;
    }
};

class CountIntervals {
public:
    // vector<pair<int,int>> intervals;
    set<pair<int,int>, Compare> intervals;
    int counter = 0;

    CountIntervals() {
        
    }
    
    void add(int left, int right) {

        // iterate through intervals
        // remove all intervals that overlap
        // keep track of min and max
        // push new final interval using min and max

        pair<int, int> currentInterval = make_pair(left, right);

        counter += right - left + 1;

        // let min and max be left and right

        // int index = 0;
        // while (index < intervals.size()) {
        
        auto it = intervals.begin();
        while (it != intervals.end()) {

            // pair<int, int> prevInterval = intervals[index];
            pair<int, int> prevInterval = *it;

            if (overlap(currentInterval, prevInterval)) {
                left = min(left, prevInterval.first);
                right = max(right, prevInterval.second);
                
                // intervals.erase(intervals.begin() + index);
                it = intervals.erase(it);
                
                int overlapSize = 0;
                // prev starts before
                if (prevInterval.first < currentInterval.first) {
                    overlapSize = 
                        min(currentInterval.second, prevInterval.second) 
                        - currentInterval.first
                        + 1;
                }
                // prev starts in the middle
                else {
                    overlapSize = 
                        min(prevInterval.second, currentInterval.second) 
                        - prevInterval.first
                        + 1;
                }
                counter -= overlapSize;

            }
            else {
                // if prev is after current, then all of the rest of prev will be after current
                if (prevInterval.first > currentInterval.second) break;

                it++;
                // index++;
            }
        }

        // intervals.push_back(make_pair(left, right));
        intervals.insert(make_pair(left, right));
    }
    
    int count() {
        return counter;
    }

    bool overlap(pair<int, int> first, pair<int, int> second) {
        return first.first <= second.first && first.second >= second.first
            || second.first <= first.first && second.second >= first.first;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */