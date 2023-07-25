 class MedianFinder {
public:
    
    // max heap
    priority_queue<int> leftQueue;
    // min heap
    priority_queue<int, vector<int>, greater<int>> rightQueue;
    bool even = true;

    MedianFinder() {
    }
    
    void addNum(int num) {

        if (leftQueue.empty()) {
            if (rightQueue.empty()) {
                leftQueue.push(num);
                even = !even;
                balanceQueues();
                return;
            }
            if (num <= rightQueue.top()) {
                leftQueue.push(num);
                even = !even;
                balanceQueues();
                return;
            }
            else {
                rightQueue.push(num);
                even = !even;
                balanceQueues();
                return;
            }
        }

        // put in left queue, if left queue has more than right, then move over
        leftQueue.push(num);
        even = !even;
        balanceQueues();
        
    }
    
    double findMedian() {
        if (even) {
            return (leftQueue.top() + rightQueue.top()) / 2.;
        }
        // else
        // cannot guarantee that right has more, need to check sizes
        // return rightQueue.top();
        return (leftQueue.size() > rightQueue.size()) ? leftQueue.top() : rightQueue.top();
    }

    void balanceQueues() {
        if (leftQueue.size() > rightQueue.size()) {
            int val = leftQueue.top();
            leftQueue.pop();
            rightQueue.push(val);
        }
        else if (rightQueue.size() > leftQueue.size()) {
            int val = rightQueue.top();
            rightQueue.pop();
            leftQueue.push(val);
        }
    }

};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */