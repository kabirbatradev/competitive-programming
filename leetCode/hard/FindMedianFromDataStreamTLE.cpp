class MedianFinder {
public:
    
    // ordered multiset
    multiset<int> leftSet;
    multiset<int> rightSet;
    // int totalCount = 0;
    bool even = true;

    MedianFinder() {
    }
    
    void addNum(int num) {
        int leftBound = *leftSet.end();
        int rightBound = *rightSet.begin();

        if (num <= leftBound) {
            leftSet.insert(num);
        }
        else {
            rightSet.insert(num);
        }
        balanceSets();
        even = !even;
    }
    
    double findMedian() {
        if (even) {
            (*leftSet.end() + *rightSet.begin()) / 2.;
        }
        // else
        return (leftSet.size() > rightSet.size()) ? *leftSet.end() : *rightSet.begin();
    }

    void balanceSets() {
        // assuming the sets are a max of 1 apart
        if (leftSet.size() - rightSet.size() > 1) {
            // left is too big
            int val = *leftSet.end();
            leftSet.erase(leftSet.end());
            rightSet.insert(val);
        }
        else if (rightSet.size() - leftSet.size() > 1) {
            // right is too big
            int val = *rightSet.begin();
            rightSet.erase(rightSet.begin());
            leftSet.insert(val);
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */