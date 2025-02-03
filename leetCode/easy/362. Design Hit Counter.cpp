class HitCounter {
public:
    HitCounter() {
        
    }

    deque<int> dq;

    /**
     * @param timestamp: the timestamp
     * @return: nothing
     */
    void hit(int timestamp) {
        dq.push_back(timestamp);
        while (!dq.empty() && dq.front() <= timestamp - 300) {
            dq.pop_front();
        }
    }

    /**
     * @param timestamp: the timestamp
     * @return: the count of hits in recent 300 seconds
     */
    int getHits(int timestamp) {
        while (!dq.empty() && dq.front() <= timestamp - 300) {
            dq.pop_front();
        }
        return dq.size();
    }

};