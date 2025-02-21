#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  // cout.precision(10); 

  while (true) {
    int n; cin >> n;
    if (n == 0) break;

    vector<int> nums(n);
  
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    // dp[0] = 1, -1
    vector<pair<int,int>> dp(n);
    dp[0] = make_pair(1, -1); // -1 here means there was no previous

    for (int i = 1; i < n; i++) {

      int maxPrevLIS = 0;
      // int minPrevVal = INT_MAX;
      int minPrevIndex = -1; // index of min value that has max LIS
      for (int k = i-1; k >= 0; k--) {

        if (nums[k] < nums[i]) {
          auto [LIS, _] = dp[k];
          if (LIS > maxPrevLIS) {
            maxPrevLIS = LIS;
            // minPrevVal = nums[k];
            minPrevIndex = k;
          }
          else if (LIS == maxPrevLIS) {
            // nums[k] was smaller and the same LIS length
            // then use it because lexographic order
            if (nums[minPrevIndex] > nums[k]) {
              // maxPrevLIS = LIS; // didnt change
              minPrevIndex = k;
            }
          }
        }
        // finished looking at old dp

      }

      dp[i] = make_pair(1 + maxPrevLIS, minPrevIndex);
      
    }

    // finished setting all dp

    // find the max LIS value
    int maxLIS = 0;
    int maxLISIndex = -1; // stores index of min value that has max LIS
    for (int i = 0; i < n; i++) {
      int LIS = dp[i].first;
      if (LIS > maxLIS) {
        maxLIS = LIS;
        maxLISIndex = i;
      }
      else if (LIS == maxLIS) {
        if (nums[maxLISIndex] > nums[i]) {
          maxLISIndex = i;
        }
      }
    }

    // can print max LIS len now
    cout << maxLIS << " ";

    // backtrack to generate solution
    int i = maxLISIndex;
    vector<int> LISbackward;
    while (i != -1) {
      // get the val
      LISbackward.push_back(nums[i]);
      // set to prev
      i = dp[i].second;
    }
    string prefix = "";
    for (int j = LISbackward.size()-1; j >= 0; j--) {
      cout << prefix << LISbackward[j];
      prefix = " ";
    }
    cout << '\n';
  }
}

/*
dp solution:

i is an index
dp[i] is the LIS that includes the ith element

dp[i] = ? 
loop backward through all the older indices (k = 0 through i-1)
for each one:
  look at value of number = nums[k]
  look at LIS that ends at index k = dp[k]
find the max dp[k] (but make sure that nums[k] < nums[i])
  if there are multiple, pick the min value nums[k]
dp[i] = 1 + max(dp[k] for all k)

how to go back and print all values:
  store at dp[i]: tuple (LIS value, the index we came from, which we called k)
*/