class Solution {
public:
    int maximumSwap(int num) {
        
        // scan from largest to smallest digit 
            // store index of digit every time number drops: 8 -> index 4
            // push that pair of values to a list "drop positions"
            // store the first digit value 
        // look for a point where digits stop decreasing and actually increased
            // this is a potential solution
            // can make a swap from larger digit to smaller digit at highest position
        // continue scanning, but only look for digits equal or larger
            // if equal, then swap this digit instead (creates bigger number)
            // if larger, then swap this digit instead, but swap it with potentially larger position value (scan through "drop positions")

        string numString = to_string(num);

        int bestSwapX = -1;
        int bestSwapY = -1;

        char currentDigit = '9'+1;
        vector<pair<char, int>> dropPositions;
        char swappedDigitValue;

        int i;
        for (i = 0; i < numString.length(); i++) {
            char c = numString[i];

            // check if the digit decreased
            if (c < currentDigit) {
                dropPositions.push_back(make_pair(c, i));
                currentDigit = c;
            }
            else if (c == currentDigit) {
                continue;
            }
            else {
                // digit increased!

                // find drop position index where value is less than digit
                for (int j = 0; j < dropPositions.size(); j++) {
                    char value = dropPositions[j].first;
                    if (value < c) {
                        // found best position to swap so far
                        bestSwapX = dropPositions[j].second;
                        bestSwapY = i;
                        swappedDigitValue = c;
                        break;
                    }
                } 
                break;
            }
        }

        // if never found decreasing point
        if (bestSwapX == -1) {
            return num;
        }

        // continue loop in phase 2: look for digit equal or larger than swapped digit value
        for ( ; i < numString.length(); i++) {
            char c = numString[i];
            if (c == swappedDigitValue) {
                bestSwapY = i;
            }
            else if (c > swappedDigitValue) {
                // found even larger digit 

                // same code as in phase 1:
                // find drop position index where value is less than digit
                for (int j = 0; j < dropPositions.size(); j++) {
                    char value = dropPositions[j].first;
                    if (value < c) {
                        bestSwapX = dropPositions[j].second;
                        bestSwapY = i;
                        swappedDigitValue = c;
                        break;
                    }
                } 
            }
        }

        // now we have swap positions
        char temp = numString[bestSwapX];
        numString[bestSwapX] = numString[bestSwapY];
        numString[bestSwapY] = temp;

        // string TO int
        return stoi(numString);
    }
};