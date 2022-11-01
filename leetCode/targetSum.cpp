class Solution {
public:
  int target;
  // vector<int> nums;

  // maps the input "next index, sumSoFar" to # combinations with that input
  // unordered_map<pair<int, int>, int> cache;
  // takes next index and maps sumSoFar to # combinations possible
  vector<unordered_map<int, int> > cache;

  int findTargetSumWays(vector<int>& nums, int target) {
    this->target = target;
    // this->nums = nums;
    for (int i = 0; i < nums.size(); i++) {
      cache.push_back(unordered_map<int, int>());
    }
    return getCombinationCount(0, 0, nums);
  }

  int getCombinationCount(int nextIndex, int sumSoFar, vector<int>& nums) {
    // returns # combinations that reach the target from this starting point

    // out of stuff to add
    if (nextIndex == nums.size()) {
      if (sumSoFar == target) {
        return 1;
      } else
        return 0;
    }

    // if currentSum in the map of the current index
    if (cache.at(nextIndex).find(sumSoFar) != cache.at(nextIndex).end()) {
      return cache.at(nextIndex).at(sumSoFar);
    }

    // else
    // compute it ourselves and then save it in the cache
    int total = 0;
    total += getCombinationCount(nextIndex + 1, sumSoFar + nums.at(nextIndex), nums);
    total += getCombinationCount(nextIndex + 1, sumSoFar - nums.at(nextIndex), nums);
    cache.at(nextIndex).insert({sumSoFar, total});
    return total;
  }
};