class Solution {
public:
    int countLargestGroup(int n) {

        map<int, int> counter;

        for (int i = 1; i <= n; i++) {
            int num = i;
            int sum = 0;

            while (num > 0) {
                sum += num % 10;
                num = num/10;
            }

            counter[sum]++;
            
        }

        int largestGroupSize = 0;
        int numberOfGroups = 0;
        for (auto [sum, count] : counter) {
            if (count > largestGroupSize) {
                largestGroupSize = count;
                numberOfGroups = 1;
            }
            else if (count == largestGroupSize) {
                numberOfGroups++;
            }
        }

        return numberOfGroups;
        
    }
};

/*
counter map
sum of digits maps to count

go through all nums from 1 to n
get sum of digits and increase count
    sum of digits = prev sum of digits + 1
    but if it was 9, then now its 1 
    and if its 19, then now its just 2
idk 
*/