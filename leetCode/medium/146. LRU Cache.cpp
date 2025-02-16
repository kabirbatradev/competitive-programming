struct Node {
    int key = 0, value = 0;
    Node *prev = nullptr, *next = nullptr;
    // Node* prev = nullptr;
    // Node* next = nullptr;
};

class LRUCache {
public:
    unordered_map<int, Node*> m;
    Node* head;
    Node* tail;
    int cap;

    LRUCache(int capacity) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        cap = capacity;
    }
    
    int get(int key) {
        if(m.count(key)) {
            moveToFront(m[key]);
            return m[key]->value;
        }
        else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(m.count(key)) {
            moveToFront(m[key]);
            m[key]->value = value;
        }
        else {
            if (m.size() == cap) {
                // have to evict last node
                Node* last = tail->prev;
                m.erase(last->key);

                // write over the last node with this new key value
                last->key = key;
                last->value = value;
                m[key] = last;

                moveToFront(last);
            }
            else {
                // add a new node, put it in front
                // Node* n = new Node{key, value, head, head->next}; // Does this work with less args too?
                Node* n = new Node{key, value}; // it does work with less args
                n->prev = head;
                n->next = head->next;
                head->next->prev = n;
                head->next = n;

                m[key] = n;
            }

        }
    }

    void moveToFront(Node* node) {
        Node* left = node->prev;
        Node* right = node->next;
        left->next = right;
        right->prev = left;

        left = head;
        right = head->next;
        node->prev = head;
        node->next = right;
        left->next = node;
        right->prev = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */