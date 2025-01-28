class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());

        int bestScore = 0;
        int currentScore = 0;

        int l = 0;
        int r = tokens.size()-1;

        while (l <= r) {
            if (power >= tokens[l]) {
                power -= tokens[l++];
                currentScore++;
                bestScore = max(bestScore, currentScore);
            }
            else if (currentScore >= 1) {
                power += tokens[r--];
                currentScore--; 
            }
            // end early if we dont have score and we dont have enough power to get score
            else {
                break;
            }
        }

        return bestScore;
    }
};