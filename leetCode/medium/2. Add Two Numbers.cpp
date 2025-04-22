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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        // return the l1 list since we will store our solution there
        ListNode* ret = l1;

        ListNode* lastL1;

        bool overflow = false;
        while (l1 != nullptr && l2 != nullptr) {
            int digit = l1->val + l2->val + overflow;
            
            if (digit >= 10) {
                overflow = true;
                digit -= 10;
            }
            else overflow = false;

            l1->val = digit;

            lastL1 = l1; // save the last 'not nullptr' l1 node

            l1 = l1->next;
            l2 = l2->next;

        }

        if (l1 == nullptr && l2 == nullptr) {
            // both lists ended
            // if there is overflow, then we need a new node
            if (overflow)
                lastL1->next = new ListNode(1);
            return ret;
        }

        if (l1 == nullptr) {
            // only l1 ended
            // swap(l1, 12) so its as if only l2 ended
            l1 = l2;
            l2 = nullptr;

            // we need to connect the linked list to l1
            lastL1->next = l1;

            // now the next condition should run
        }


        if (l2 == nullptr) {
            // only l2 ended
            while (l1 != nullptr) {
                l1->val += overflow;
                if (l1->val >= 10) {
                    // overflow = true; // doesnt do anything
                    l1->val -= 10;
                }
                // no more overflow
                // so we can just return the rest of the list
                else {
                    return ret;
                }

                lastL1 = l1;

                l1 = l1->next;
            }
            // can only be here if last digit had overflow and it ended
            lastL1->next = new ListNode(1);
            return ret;

        }
        
        

        return ret;
        
    }
};

/*
rightmost digit is first
just add them
if overflow, then max overflow is just 1
so then add 1 extra to next computation

repeat until one list ends
then add remaining overflow to second list
if its not all '9's, then we can just add the rest of that list to the end
    instead of looping through the rest of that list

if it ends with a '9' that overflows, we need to create a new '1' node
like 95 + 6 ends with a 9 that overflows 

what if we store our solution in l1's nodes? is that faster?
in real code, that probably causes memory issues (leaks or double frees)
but it also reduces # allocations on heap
*/