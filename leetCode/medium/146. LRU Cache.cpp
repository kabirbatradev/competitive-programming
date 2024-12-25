struct Node {
    int value;
    int key; // required to go back into map and delete
    Node *prev = nullptr;
    Node *next = nullptr;
    Node(int key, int value) : key(key), value(value) {}
};

class LRUCache {
public:
    // linked list: queue of least recently used values
        // head: dummy node representing least recently used
        // tail: dummy node where you can place most recently used right before
    // map: from key to linked list node for quick access
    Node *head;
    Node *tail;
    unordered_map<int, Node*> m;
    int maxSize;
    LRUCache(int capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
        
        maxSize = capacity;
    }
    
    int get(int key) {
        // cout << "get " << key << endl;
        if (m.count(key)) {

            // dont forget to remove and put in the back (because the item is used)
            // remove the node from list
            m[key]->prev->next = m[key]->next;
            m[key]->next->prev = m[key]->prev;

            // assign prev and next
            m[key]->next = tail;
            m[key]->prev = tail->prev;

            // insert it at the end
            tail->prev->next = m[key];
            tail->prev = m[key];

            // return the value!
            return m[key]->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        // cout << "put " << key << " " << value << endl;
        // val alr exists, so just update and push to end of queue
        if (m.count(key)) {
            m[key]->value = value; // update value

            // remove the node from list
            m[key]->prev->next = m[key]->next;
            m[key]->next->prev = m[key]->prev;

            // assign prev and next
            m[key]->next = tail;
            m[key]->prev = tail->prev;

            // insert it at the end
            tail->prev->next = m[key];
            tail->prev = m[key];
            return;
        }
        // check if deletion is required
        if (m.size() == maxSize) {
            // delete the node at the front:
            // int deleteVal = head->next->value;
            // get delete key: 
            int deleteKey = head->next->key;
            // cout << deleteKey << endl;
            m.erase(deleteKey);

            // remove node from list
            Node *toDelete = head->next;
            head->next = head->next->next;
            head->next->prev = head;
            delete toDelete;
        }
        // otherwise/now we are free to insert
        m[key] = new Node(key, value); // creates a new node, increases size of map

        // assign prev and next
        m[key]->next = tail;
        m[key]->prev = tail->prev;

        // insert into linked list at the end
        tail->prev->next = m[key];
        tail->prev = m[key];
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */