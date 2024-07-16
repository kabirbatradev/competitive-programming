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
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode* curr = head;
        for (int i = 0; i < n; i++) {
            curr = curr->next;
        }
        ListNode* offsetNode = head;

        ListNode* prev = nullptr;
        while (curr != nullptr) {
            curr = curr->next;
            if (prev == nullptr) prev = head;
            else prev = prev->next;
            offsetNode = offsetNode->next;
        }

        if (prev != nullptr)
            prev->next = offsetNode->next;

        if (offsetNode == head) return head->next;
        return head;
    }
};