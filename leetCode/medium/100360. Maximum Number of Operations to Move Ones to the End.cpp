class Solution {
public:
    int maxOperations(string s) {

        // rule of thumb: move 1s on the left first 
        // (because moving something on the right first is always 
        // worse because we could have done more moves by doing left right left instead of right left

        // if all 1s are in a row, then every single one moves together 
        // (multiplying the value of the move) 
            // therefore, multiple 1s in a row can be represented as a stack of a certain value
            // we would need an int array maybe?
        
        // we just need a way to keep track of the current stack size

        
        int i = 0;
        while (true) {
            if (i == s.length()) return 0; // case of all 0s
            char c = s[i];
            if (c == '0') {
                i++;
            }
            else {
                break;
            }
        }

        int operationCounter = 0;
        int currentStackSize = 0;
        // now string at i is guaranteed to be a '1'
        while (true) {
            currentStackSize += 1;
            // three cases: 
            
            // next = end
                // we cant move so just end? no operations possible
            if (i+1 == s.length()) break;
            
            // next = 0 means we can do operations!
            if (s[i+1] == '0') {

                // find the next index that has a 1 or end
                i = i+2;
                while (i < s.length() && s[i] == '0') {
                    i++;
                }

                // imagine moving the stack optimally 
                operationCounter += currentStackSize;

                if (i == s.length()) break; // break if we moved the stack to the end

                // i is now at the index of the next '1'
                continue;
            }

            // otherwise the next char is also 1, so we cant do operations
            // next loop will automatically increase stack size
            i++; // get it to the index of the next '1'

            // if (s[i+1] == '1') {
            //     currentStackSize++;
            //     i++;
            //     continue;
            // }


        }

        return operationCounter;
        
    }
};