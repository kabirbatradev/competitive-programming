class Solution {
  public:
      int numRabbits(vector<int>& answers) {
  
          map<int, int> counter;
  
          for (int num : answers) {
              num++; // 1 means 2 rabbits like this
              counter[num]++;
          }
  
          int total = 0;
          for (auto [num, count] : counter) {
              // if count is higher than num, then there are more
  
              // count = num means just count
              // count is one greater than num means 6 rabbits said there are 5 like me including me
              // so i want division that rounds up
  
              // round up division trick for 'count / num'
              int multiplier = (count+num-1) / num;
              total += num * multiplier;
          }
  
          return total;
  
          
      }
  };
  