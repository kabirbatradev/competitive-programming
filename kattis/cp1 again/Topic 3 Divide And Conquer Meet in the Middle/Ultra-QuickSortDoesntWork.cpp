#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);

  int n; cin >> n;

  vector<int> unsorted(n);

  for (int i = 0; i < n; i++) {
    int ai; cin >> ai;
    unsorted[i] = ai;
  }

  vector<int> sorted(unsorted);
  sort(sorted.begin(), sorted.end());

  for (int i = 0; i < n; i++) {
    cout << unsorted[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < n; i++) {
    cout << sorted[i] << " ";
  }
  cout << endl;


  // digit --> index in sorted
  unordered_map<int, int> m;
  for (int i = 0; i < n; i++) {
    int x = sorted[i];
    m[x] = i;
  }

  int swaps = 0;
  priority_queue<int> pq;
  int j = 0; // j is like a virtual index for if we actually did the swaps
  for (int i = 0; i < n; i++, j++) {

    // if something at the top of the pq has been passed, then remove and increment j 
    while (!pq.empty() && pq.top() < i) {
      cout << "popping " << pq.top() << " from pq" << endl;
      pq.pop();
    }

    int x = unsorted[i]; // get digit at i (new digit to consider)

    cout << i << " " << j << " " << x << " " << m[x] << endl;

    // no swap needed if already correct position 
    // if (m[x] == i) continue; 
    // compare with j because that is where this would be after swaps
    if (m[x] == j) {
      continue; 
    }

    // otherwise swap this element with where it is supposed to go
    // supposed to go to m[x]
    cout << "moving " << j << " to " << m[x] << endl;
    // swap(unsorted[m[x]], unsorted[i]);
    // swaps++;
    // // note, the element here now is probably still wrong, so decrement i to process it again
    // i--;

    // instead of swapping, we would do virtual swaps
    int distance = m[x] - j; // i is always before because everything before i should be "sorted"
    cout << "distance = " << distance << endl;
    swaps += distance;
    // i gets incremented, but j stays the same
    j--; // decrement to make it the same next iteration
    // and we need to add where it was swapped to the pq so that we can bring j back aligned there
    pq.push(m[x]);

  }

  for (int i = 0; i < n; i++) {
    cout << unsorted[i] << " ";
  }
  cout << endl;


  cout << swaps << '\n';
}

/*
observation: 
if a digit is x distance away from its sorted position, then it needs to swap x times to get there
  everything between digit start and end are kept in the same order
moving a single digit 5 swaps to the right is the same as moving all 5 digits in between 1 swap to the left

what if we just swapped every digit to where it wants to be? would everything naturally align? with minimum swaps?
  simulating this can be expensive (imagine reversing a long array... that would be n^2 swaps)
how do we get the count without simulating?
  dont actually move the element (no swap)
  push each swapped element's new position index to min heap (pq with greater<int>),
  then instead of shifting everything over, go to the next index (i++), and have a virtual index j which is still the old i (not incremented)
  and just add the number of swaps that would have happened
  then as you push i forward, eventually you will get to a value in the pq: position where something was swapped to
    once i passes that value in the pq, we have passed where the element was swapped, so we can increment virtual index j
    so that j is aligned for the rest of the array
sample case:
  3 0 1 2 ... (like 5 6 7)
  here, the 3 swaps forward 3 positions (3 swaps)
  insert end position = 3 to the pq
  i++ -> i = 1
  but j = 0
  so 0 matches j = 0 and no swaps for digits 0 1 and 2
  once we pass end position = 3 from pq, we increment j to say we passed where the "3" was 
  so then j and i are aligned again for remaining elements\

  wait the position that an object was pushed to could have been moved in another swap

  what if we just simulate all the swaps? will it be too slow?
  with 500,000 numbers, n^2 is too slow..

*/