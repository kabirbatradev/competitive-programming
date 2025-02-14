#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  ll swaps = 0;

  Solution() {
    int n; cin >> n;

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
    }

    mergeSortCountSwaps(arr);

    cout << swaps << '\n';
  }

  void mergeSortCountSwaps(vector<int>& arr) {
    int size = arr.size();
    // no swaps if size array is 1 or 0, already sorted
    if (size <= 1) return;

    // split array ranges:
      // 0, size/2
      // size/2, size
    vector<int> leftArr(size/2, 0);
    vector<int> rightArr(size - size/2, 0);

    // write into two sub arrays
    for (int i = 0; i < arr.size(); i++) {
      if (i < leftArr.size()) {
        leftArr[i] = arr[i];
      }
      else {
        // if (i - leftArr.size() >= rightArr.size()) {
        //   cout << "ERROR what" << endl;
        // }
        rightArr[i - leftArr.size()] = arr[i];
      }
    }

    mergeSortCountSwaps(leftArr);
    mergeSortCountSwaps(rightArr);

    int left = 0;
    int right = 0;
    int arrPointer = 0;
    // while both pointers havent reached their ends
    while (left < leftArr.size() || right < rightArr.size()) {
      // if right reached end, then just fill arr with the rest of the left array
      // if left pointer element is smaller, then we can place it first
      // but also do not do this if left already reached the end
      if (left != leftArr.size() && (right == rightArr.size() || leftArr[left] < rightArr[right])) {
        arr[arrPointer] = leftArr[left];
        arrPointer++;
        left++;
      }
      // if right pointer element is smaller, we have to do swaps
      else {
        arr[arrPointer] = rightArr[right];
        arrPointer++;
        right++;
        swaps += leftArr.size() - left;
      }
    }

    return;
  }

};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}

/*
merge sort idea:
split into 2 subarrays
count # swaps in the subarrays
merge: need to make more swaps to move number to the correct position

note: the core of the solution is in the merge
how do we do the merge:
  hint: its similar to merge sort
  left array and right array are already sorted
  2 pointers (start of each array)
  if left pointer element is smaller, then push pointer
  if right pointer element is smaller, then you have to swap it to the left
    # swaps = (left array size) - (left pointer index)
    dont add (right pointer index) because that would have already been swapped
*/