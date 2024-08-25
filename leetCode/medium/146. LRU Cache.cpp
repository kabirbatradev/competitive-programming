class LRUCache {
public:
    struct valueAndCount {
        int val;
        int count;
    }; 
    // key to value,count
    unordered_map<int, valueAndCount> m;

    // queue keeping track of order of puts (keys)
    queue<int> q;

    int cap;
    LRUCache(int capacity) {

        cap = capacity;
        
    }
    
    int get(int key) {
        if (m.count(key) == 0) return -1;

        // get counts as using; update count and add to timeline queue
        m[key].count++;
        q.push(key);

        return m[key].val;
    }
    
    void put(int key, int value) {
        // new element
        if (m.count(key) == 0) {
            
            if (m.size() == cap) {

                // need to remove something first
                while(true) {
                    int keyToRemove = q.front();
                    q.pop();
                    m[keyToRemove].count--;
                    if (m[keyToRemove].count == 0) {
                        // this element is not in the queue timeline at all, it is the oldest 
                        m.erase(keyToRemove); // decreases the size
                        break;
                    }
                }

            }

            // now there is "space" for new element
            m[key] = valueAndCount(value, 1); // inserts to m, increasing the size
            q.push(key);
        }
        else {
            // update:
            // update val, add to count, push to queue
            m[key].val = value;
            m[key].count++;
            q.push(key);

        }
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */