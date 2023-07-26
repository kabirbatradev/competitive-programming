 class MedianFinder {
public:
    
    // max heap
    priority_queue<int> leftQueue;
    // min heap
    priority_queue<int, vector<int>, greater<int>> rightQueue;

    MedianFinder() {
    }
    
    void addNum(int num) {

        if (leftQueue.size() > rightQueue.size()) {
            // left has more elements, so put left and shift the biggest over
            leftQueue.push(num);

            int val = leftQueue.top();
            leftQueue.pop();
            rightQueue.push(val);
        }
        else {
            // right has more elements, so put right and shift smallest over
            rightQueue.push(num);

            int val = rightQueue.top();
            rightQueue.pop();
            leftQueue.push(val);
        }
        
    }
    
    double findMedian() {
        if (leftQueue.size() == rightQueue.size()) {
            return (leftQueue.top() + rightQueue.top()) / 2.;
        }
        // return element from larger queue (will probably always be the left queue)
        return (leftQueue.size() > rightQueue.size()) ? leftQueue.top() : rightQueue.top();
    }

};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */