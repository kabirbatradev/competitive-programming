// note that this is lintcode 919 · Meeting Rooms II
/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {

        if (intervals.size() == 0) return 0;

        // use greater<int> to make the pq a min heap instead of max heap
        priority_queue<int, vector<int>, greater<int>> startTimes;
        priority_queue<int, vector<int>, greater<int>> endTimes;
        for (int i = 0; i < intervals.size(); i++) {
            startTimes.push(intervals[i].start);
            endTimes.push(intervals[i].end);
        }
        
        int mostConcurrentMeetings = 0;

        int currentConcurrentMeetings = 0;
        // if we are out of start times, then we cant add any new meetings
        while (!startTimes.empty()) {
            // cout << startTimes.top() << " " << endTimes.top() << endl;
            // if (startTimes.top() <= endTimes.top()) {
            if (startTimes.top() < endTimes.top()) {
                startTimes.pop();
                currentConcurrentMeetings++;
            }
            else {
                endTimes.pop();
                currentConcurrentMeetings--;
            }
            mostConcurrentMeetings = max(mostConcurrentMeetings, currentConcurrentMeetings);
            // cout << currentConcurrentMeetings << endl;
        }

        return mostConcurrentMeetings;


    }
};