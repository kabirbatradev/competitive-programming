class Solution {
  public:
      int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
  
          unordered_map<int, int> sumCounts;
          
          for (int a : nums1) {
              for (int b : nums2) {
                  int sum = a + b;
                  sumCounts[sum]++;
              }
          }
  
          int count = 0;
          for (int a : nums3) {
              for (int b : nums4) {
                  int target = 0 - (a + b);
                  count += sumCounts[target];
              }
          }
  
          return count;
          
      }
  };
  
  /*
  meet in the middle
  
  hash table: sum -> count (number of ways to get that sum)
      first 2 arrays, all possible sums
  
  first 2 arrays:
      get all pairs of numbers
      target = -sum
      find target in hash table
      increment a total count with count from hash table
  
  */