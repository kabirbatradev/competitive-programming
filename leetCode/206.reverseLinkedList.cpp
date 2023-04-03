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
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

        ListNode *first, *second, *third;
        first = head;
        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == nullptr) {
            return head;
        }
        second = first->next;
        first->next = nullptr;
        if (second->next == nullptr) {
            head->next = nullptr;
            second->next = head;
            return second;
        }
        third = second->next;
        while (true) {
            // first->next = nullptr;
            second->next = first;

            first = second;
            second = third;
            third = second->next;
            if (third == nullptr) {
                second->next = first;
                return second;
            }
        }
        
    }
};