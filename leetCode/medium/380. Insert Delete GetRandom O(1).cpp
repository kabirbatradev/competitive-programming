class RandomizedSet {
public:
    vector<int> numbers;
    unordered_map<int, int> numberToListIndex;

    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        // if alr exists, no insert
        if (numberToListIndex.count(val)) {
            return false;
        }

        numbers.push_back(val);
        numberToListIndex[val] = numbers.size()-1;
        return true;
    }
    
    bool remove(int val) {
        // exists, so remove
        if (numberToListIndex.count(val)) {
            int index = numberToListIndex[val]; // get index in vector of the val so we can delete it
            
            // move last element to this index
            int valOfLast = numbers.back();
            numbers[index] = valOfLast;
            numbers.erase(numbers.end()-1); // erase last element from vector
            numberToListIndex[valOfLast] = index; // update mapping

            numberToListIndex.erase(val); // erase the map entry of val
            // this is in the end in the case where valOfLast = val

            return true;
        }
        // does not exist
        return false;
    }
    
    int getRandom() {
        int index = rand() % numbers.size();
        return numbers[index];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */