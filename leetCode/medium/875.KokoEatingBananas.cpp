class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        
        int max = 0;
        for (int& pile : piles) {
            if (pile > max) max = pile;
        }
        // longest pile needs to be eaten in an hour
        int maxEatingSpeed = max;

        // min eating speed (at least 1 pile, at least one banana)
        int minEatingSpeed = 1;

        int bestAnswer = maxEatingSpeed;
        // binary search the answer
        while (maxEatingSpeed >= minEatingSpeed) {
            int mid = (maxEatingSpeed + minEatingSpeed) / 2;
            bool success = canEat(mid, piles, h);
            // cout << mid << " " << success << endl;

            // if success, then move max down
            if (success) {
                bestAnswer = mid;
                maxEatingSpeed = mid - 1;
            }
            // otherwise move min up
            else {
                minEatingSpeed = mid + 1;
            }

        }
        return bestAnswer;
    }

    bool canEat(int& k, vector<int>& piles, int& h) {
        // cout << "input is " << k << endl;
        long hoursNeeded = 0; // hoursNeeded can exceed int max
        for (int& pile : piles) {
            if (pile < k) {
                hoursNeeded++;
                // cout << "first: " << pile << endl;
            }
            else {
                hoursNeeded += ceil((double)pile / (double)k);
                // cout << "second: " << pile << " hours: " << hoursNeeded << endl;
            }
        }
        return hoursNeeded <= h;
    }
};