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
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {

        vector<vector<int>> spiral(m, vector<int>(n, -1));
        
        // right, down, left, up
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        int x = 0; int y = 0;
        int currentDir = 0;
        while (true) {
            spiral[y][x] = head->val;
            head = head->next;
            
            if (head == nullptr) break;

            int newX = x + dx[currentDir];
            int newY = y + dy[currentDir];

            // out of range or visited, then change direction
            if (
                newX < 0 || newY < 0 || newY >= m || newX >= n
                || spiral[newY][newX] != -1
            ) {
                currentDir = (currentDir + 1) % 4;
                newX = x + dx[currentDir];
                newY = y + dy[currentDir];
            }

            x = newX;
            y = newY;
        }

        return spiral;
    }
};