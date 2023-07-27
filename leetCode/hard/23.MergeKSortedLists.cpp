/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


class Pair {
public:
    int val;
    ListNode* node;
    
    Pair(int value, ListNode* listNode) {
        val = value;
        node = listNode;
    }   

    // custom < operator
    // pq should be min heap instead of defeault (switch < to >)
    bool operator<(const Pair& other) const {
        return val > other.val;
    }
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<Pair> pq;
        ListNode* head = nullptr;
        ListNode* currentNode = nullptr;

        // initialze pq with start pointers
        for (ListNode* head : lists) {
            if (head == nullptr) continue;
            pq.push(Pair(head->val, head));
        }

        while (!pq.empty()) {

            // get next node of that list
            Pair p = pq.top();
            ListNode* thisNode = p.node;
            ListNode* nextNode = thisNode->next;

            // add next node to pq (if its not end of list)
            if (nextNode != nullptr)
                pq.push(Pair(nextNode->val, nextNode));

            // add this node to final list
            if (head == nullptr) {
                head = thisNode;
                currentNode = thisNode;
            }
            else {
                currentNode->next = thisNode;
                currentNode = thisNode;
            }
            
            pq.pop();
        }

        // last node next should be null (it should already be)
        // currentNode->next = nullptr;

        return head;
    }
};
