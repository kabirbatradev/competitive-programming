class CustomStack {
public:
    int items;
    int size;
    vector<int> stack;
    vector<int> increments;
    CustomStack(int maxSize) {
        stack = vector<int>(maxSize);
        increments = vector<int>(maxSize, 0); // init to 0 because its not overwritten
        items = 0;
        size = maxSize;
    }
    
    void push(int x) {
        if (items == size) return;
        stack[items] = x;
        items++;
    }
    
    int pop() {
        if (items == 0) return -1;
        items--;
        int ret = stack[items] + increments[items];

        // build up increments (push onto previous)
        if (items != 0) 
            increments[items-1] += increments[items];
        // dont forget to remove increment at position that no longer exists
        increments[items] = 0;

        return ret;
    }
    
    void increment(int k, int val) {
        // for (int i = 0; i < k && i < size; i++) {
        //     stack[i] += val;
        // }
        if (items == 0) return;
        int index = min(k-1, items-1);
        increments[index] += val;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */