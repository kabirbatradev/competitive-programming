class Solution {
  public:
      int numberOfArrays(vector<int>& differences, int lower, int upper) {
          using ll = long long;
          ll curr = 0;
          ll big = 0;
          ll small = 0;
          for (ll num : differences) {
              curr += num;
              big = max(big, curr);
              small = min(small, curr);
  
              // cout << curr << " ";
          }
          // cout << endl;
  
          // cout << big << " " << small << endl;
  
          ll range = big - small;
          // cout << range << endl;
  
          ll givenRange = upper - lower;
          // cout << givenRange << endl;
  
          // off by one error because range given is inclusive, so size is 1 larger
          ll ans = givenRange - range + 1; 
          if (ans < 0) return 0;
  
          return (int)ans;
      }
  };
  
  /*
  use differences starting at 0
  keep track of min poll and max poll
      this gives us a range
      note that there is no starting value, so we can shift by any amount
  compare this to range given by lower and upper
  
  number of ways = difference in sizes of ranges
  */