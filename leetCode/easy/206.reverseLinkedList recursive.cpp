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
    ListNode* reverseList(ListNode* head) {
        // guarantee we next is not null to guarantee reversed is not null
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* next = head->next;
        ListNode* reversed = reverseList(next);

        // next is now at the end of the second linkedlist, so put head after that
        next->next = head;
        head->next = nullptr;
        return reversed;
    }
};