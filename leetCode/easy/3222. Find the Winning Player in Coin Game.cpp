class Solution {
public:
    string losingPlayer(int x, int y) {

        // 1x, 4y = 115
        bool aliceTurn = true;
        while (true) {
            x -= 1;
            y -= 4;
            if (x < 0 || y < 0) {
                break;
            }
            aliceTurn = !aliceTurn;
        }
        aliceTurn = !aliceTurn;
        return aliceTurn ? "Alice" : "Bob";
        
    }
};