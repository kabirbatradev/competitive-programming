class Solution {
  public:
      double average(vector<int>& salary) {
  
          auto [min, max] = minmax_element(salary.begin(), salary.end());
          // returns pair of iterators
  
          int sum = accumulate(salary.begin(), salary.end(), 0);
  
          return ((double)sum - *min - *max) / (salary.size() - 2);
      }
  };