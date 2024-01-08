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
    ListNode* middleNode(ListNode* head) {

        // when fast reaches the end, then slow should be in the middle

        ListNode* fast = head;
        ListNode* slow = head;
        while (true) {
            if (fast->next == nullptr) break;
            fast = fast->next;

            // since fast was able to push forward 1, 
                // to make sure slow is the second middle, slow should push forward too

            slow = slow->next;

            // push fast again so that it is always double the distance ahead of slow
            if (fast->next == nullptr) break;
            fast = fast->next;
        }

        return slow;
        
    }
};