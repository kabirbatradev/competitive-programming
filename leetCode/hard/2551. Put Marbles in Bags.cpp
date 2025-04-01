class Solution {
  public:
      long long putMarbles(vector<int>& weights, int k) {
          if (k == 1) return 0;
          
          // k-1 pairs min max
  
          // vector approach: (much faster, better memory)
          int n = weights.size();
          vector<int> pairSums(n-1);
          for (int i = 0; i < weights.size()-1; i++) {
              pairSums[i] = weights[i] + weights[i+1];
          }
          sort(pairSums.begin(), pairSums.end());
          
          // add the last k-1 elements, subtract the first k-1 elements
          long long ans = 0;
          for (int i = 0; i < k-1; i++) {
              ans += pairSums[n-2-i] - pairSums[i];
          }
          return ans;
  
  
          // heap approach:
  
          priority_queue<int> maxHeap;
          priority_queue<int, vector<int>, greater<int>> minHeap;
          for (int i = 0; i < weights.size()-1; i++) {
              int pairSum = weights[i] + weights[i+1];
  
              maxHeap.push(pairSum);
              if (maxHeap.size() > k-1) maxHeap.pop();
  
              minHeap.push(pairSum);
              if (minHeap.size() > k-1) minHeap.pop();
          }
  
          long long minSum = 0;
          long long maxSum = 0;
          for (int i = 0; i < k-1; i++) {
              // max heap has 5 min elements bc we popped the max ones
              minSum += maxHeap.top(); maxHeap.pop();
              // min heap has 5 max elements
              maxSum += minHeap.top(); minHeap.pop();
          }
          return maxSum - minSum;
      }
  };