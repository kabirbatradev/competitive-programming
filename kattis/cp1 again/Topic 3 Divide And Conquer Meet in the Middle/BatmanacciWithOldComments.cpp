// Author: Kabir batra
// It is okay to share my code for educational purposes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Solution {

  vector<ll> fibonacciNumbers;

  int lastGeneratedFibNum;

  Solution() {
    ll n; ll k;
    cin >> n >> k;

    // int s1 = N;
    // int s2 = A;

    // populate the fibonacciNumbers list
    generateNFibonacciNumbers(n);

    // note this pattern: the first number is 
      // N if n is odd
      // A if n is even

    // passing in n-1 because 0 index offset
    cout << (boilDownFibNum(n-1, k-1) ? 'N' : 'A') << '\n';

    // just curious... it was 91
    // cout << lastGeneratedFibNum << endl;

  }

  // return true if N
  bool boilDownFibNum(int currentFibNum, ll k) {
    // if we have boiled down to first or second fib num, then return its obvious which N or A
    if (currentFibNum <= 1) {
      // return true = N if num is 0 aka first fib num, and false = A if num is 1 aka second fib num
      return currentFibNum == 0;
    }

    // if trying to search within a string whos size = fib num that cannot fit in long long
    if (currentFibNum > lastGeneratedFibNum) {
      // then we know the string starts with either the string of size
        // lastGeneratedFibNum or lastGeneratedFibNum-1
      // depending on which parity it matches with (even or odd)
      // pass in the same k because k is smaller than the last generated fib num because k < long max
      if (currentFibNum % 2 == lastGeneratedFibNum % 2) {
        return boilDownFibNum(lastGeneratedFibNum, k);
      }
      else {
        return boilDownFibNum(lastGeneratedFibNum-1, k);
      }

    }

    // get 2 prev fib nums representing 2 previous strings
    ll first = fibonacciNumbers[currentFibNum-2]; // = length of first half of the current string
    ll second = fibonacciNumbers[currentFibNum-1];

    // if k fits in the first half, then split the first half with the same k
    // k is in [0, first-1]
    if (k < first) {
      return boilDownFibNum(currentFibNum-2, k);
    }
    // otherwise, k is in the second half of the string, so search in the second string
    // k is now offset by size of first string part
    else {
      return boilDownFibNum(currentFibNum-1, k - first);
    }
    
  }

  // function to generate a list of n fib numbers
  void generateNFibonacciNumbers(int n) {
    // Reconsider reserving the whole array: 
      // at around the 91st fibonacci number, it no longer fits in a long, so the rest of the space is wasted
    fibonacciNumbers = vector<ll>(n);

    fibonacciNumbers[0] = 1;
    fibonacciNumbers[1] = 1;

    for (int i = 2; i < n; i++) {
      // long max: LLONG_MAX
      if (LLONG_MAX - fibonacciNumbers[i-1] < fibonacciNumbers[i-2]) {
        // will go out of bounds
        lastGeneratedFibNum = i-1;
        return; // exit after marking where we stopped
      }
      fibonacciNumbers[i] = fibonacciNumbers[i-1] + fibonacciNumbers[i-2];
    }

    // if we got here, we got through the whole loop and generated all fib nums successfully
    lastGeneratedFibNum = n-1;

  }

};

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin.exceptions(cin.failbit);
  Solution s;
}

/*
trick: get the nth fibonacci number to get the length of the nth string

Note: the letter that the string starts with always alternates between N and A
  even numbered strings start with A
  consecutive strings start with opposite letter

we can "binary search" the value of the kth letter
  by breaking the string into the 2 strings that made it, and doing that repeatedly

  if the string length is even, then split it evenly
  if the string length is odd, then include the middle element in the right split

  wait no we cant split it in half everytime because n = 4 is ANA and n = 5 is NAANA and n = 6 is size 8, 
  and if we split that in half, we would have 4 and 4, which is wrong 
    ANAN and AANA both start with A, so our assumption doesnt hold
  
what if instead, we generated all n=10^5 fibonacci numbers and stored them in an array
  then we could split the last number into the past 2 fibonacci numbers
    because we know the size of the past 2
  and we can figure out in which one is k
  and then repeatedly split that number
  eventually we would figure out which fibonacci number of size= 1 k is in (either s1 or s2)

algo:
  you know current fib num
  if fib num is 1 or 2, then this is base case
  otherwise, 
    get previous 2 fib nums
    check if k is in either first one or second one
    offset k so that now you are searching for new kth num of this new fib num
      if k is in first fib num, then no offset for k
      if k > first fib num, then pass in k - first fib num

edge case:
  fib number is larger than long long
  then the string either starts with x or y, where x and y are the last two fibonacci numbers before they could not be stored anymore
  so we can detect the last one that can be stored in a long long
  and then if y is the last fib number and y has the same parity as n (both even or both odd), then the string starts with y
  otherwise it starts with x
  so then we can perform the k algorithm on x or y

*/
