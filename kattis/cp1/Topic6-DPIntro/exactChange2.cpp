

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;
using ll = long long;

// ll is kinda op pog use it ALWAYS

// #define PI 3.1415926535897932384626433832795

typedef struct answerStruct {
  vector<int> bestBillList;
  int billCount; // same as bestBillList.size()
  int amountOfChange;

  // store the bills remaining takes space
  // vs calculate them on the spot takes time
  // i say we try to store it
  
  vector<int> remainingBills;

} answer;


vector<int> allBills;
vector<answer> answerKey;


answer whatIsTheBestSolutionToPrice(int price) {

  // what if they ask for price = 0? // just return empty stuff
  // what if they ask for a negative price? // same as if price was 0
  if (price <= 0) {
    answer ans;
    // ans.bestBillList
    ans.billCount = 0;
    ans.amountOfChange = -price; // if the price is negative,
    // that means you just payed with a bill that was more than the price. 
    ans.remainingBills = allBills;
    return ans;
  }

  // what if they ask for a positive price // then continue recursing till we get to <= 0
  answer ans = answerKey.at(price);

  if (ans.amountOfChange == -1) {
    // not solved yet (not already in the answerKey), use recursion

    // iterate through all the bills and store the best solution so far
    answer bestSolution = {};
    bool bestSolutionNotSet = true;

    for (int i = 0; i < allBills.size(); i++) {
      // cout << "calling function with " << price << " - " << allBills.at(i) << endl;
      answer newPriceAnswer = whatIsTheBestSolutionToPrice(price - allBills.at(i));

      // if the bill allBills.at(i) is in the remaining bills, then we are clear
      // if the bill is in remaining bills, then remove it from the remaining
      
      if (
        find(
          newPriceAnswer.remainingBills.begin(),
          newPriceAnswer.remainingBills.end(),
          allBills.at(i)
        ) != newPriceAnswer.remainingBills.end()
      ) {
        // bill was found in the remaining bills

        answer possibleSolution;
        possibleSolution.amountOfChange = newPriceAnswer.amountOfChange;
        possibleSolution.bestBillList = newPriceAnswer.bestBillList;
        possibleSolution.bestBillList.push_back(allBills.at(i));
        possibleSolution.billCount = newPriceAnswer.billCount;
        possibleSolution.billCount++;
        possibleSolution.remainingBills = newPriceAnswer.remainingBills;
        possibleSolution.remainingBills.erase(find(
          possibleSolution.remainingBills.begin(),
          possibleSolution.remainingBills.end(),
          allBills.at(i)
        ));

        if (bestSolutionNotSet) {
          bestSolution = possibleSolution;
          bestSolutionNotSet = false;
        }
        else {
          // compare the best with this possible one

          if (possibleSolution.amountOfChange < bestSolution.amountOfChange) {
            bestSolution = possibleSolution;
          }
          else if (possibleSolution.amountOfChange == bestSolution.amountOfChange) {
            if (possibleSolution.billCount < bestSolution.billCount) {
              bestSolution = possibleSolution;
            }
          }

          // otherwise this solution sucks
          // and we can just leave alone the best solution so far

        }
      }
      else {
        continue;
      }
      
    }

    // after the for loop ends, we return the best answer we have got so far
    // also update the dp array
    answerKey.at(price) = bestSolution;
    return bestSolution;

  }
  else {
    // already solved, just return answer
    return ans;
  }

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  // cout.precision(10);

  answerKey.reserve(10001);
  // index 10,000 is for price = 10,000

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int price;
    cin >> price;

    answer notSolvedYet;
    notSolvedYet.amountOfChange = -1;

    for (int i = 0; i < 10001; i++) { 
      answerKey.push_back(notSolvedYet);
    }


    int billCount;
    cin >> billCount;
    vector<int> bills;
    bills.reserve(billCount);
    for (int j = 0; j < billCount; j++) {
      int currentBill;
      cin >> currentBill;
      bills.push_back(currentBill);
    }

    allBills = bills;

    answer ans = whatIsTheBestSolutionToPrice(price);
    cout << price + ans.amountOfChange << " " << ans.billCount << endl;

  }

}


// ideas?
// well we want least bills and we want minimum change
// without the last (smallest) bill given, say the problem is solved
// now the last bill is introduced
// add it
// if we have not reached goal price, then just keep going lol
// if we had already passed the goal price, then
  // we have to try to find the best possible combination, now with this new bill
  // let x = how much we overshoot
  // recursively go through the entire solution set, and mess with it while
  // keeping track of the best so far
  // delete smaller values first, keep deleting until we stopped overshooting,
    // the recursive alg does a for loop but breaks when we try to delete a 
    // value that is greater than the overshoot itself (assuming the solution
    // is sorted from least to greatest)
  // store the best combination of not overshooting

  // okay but what if the optimal solution involes a value that was not used in
  // the original solution?



// new idea
// what if we brute force
// simply iterate through every possibly combination of bills until you get one that
// overshoots the least and has the least combinations
// this is just recursion complete search kind of stuff but /shrug
// is it worth a shot until I can come up with a better idea? Sure!
  // make a function that takes in (currentSequence, remainingBills)
  // also global variables for
  // bestList, bestOvershoot, bestNumberOfBills
// the function:
  // iterates through the entire remainingBills
  // takes the currentSequence and adds a remainingBill
  // passes that to the function again
  // if it overshoots, then thats okay
  // if it has already overshoot, then compare with the global variables
    // dont call the function again if has already overshoot
  // if it still hasnt overshoot, just keep going?
  // if bestNumberOfBills has been passed, then we can stop this recursive run
  // also, if we run out of bills, we shouldve overshot the price anyway,
  // so basically dont need to worry that remaining bills is empty

// one thing i notice: we are taking the sum of groups of bills that maybe
// we have already taken the sum of
// imagine making one of those sum matricies
// that would be interesting but I dont see how it would be useful right now
// since the sums vary and can have missing elements in the set
// so we can't really predetermine sums



// new more dp related idea:
// lets try to solve this with the exact change approach
// exact change asks to hold a 1d array where each index tells you 
// the best possible combination of coins you can use to reach it
  // I think i misinterpretted this earlier (it is not the best solution given a certain element
  // but instead the best solution given that is the price we are trying to find a solution for)
// basically, remind yourself that dp is always about storing an array of answers to potential
// questions, where the index is the question
// In this problem, the question is the price would be the index for the array, where price maxes out at
// 10,000 so, we have 10,000 elements in our array at max

// then we ask: What is the best solution to price = 1500?
// break that into "what is the best solution for p = 1000" + 500 bill used
// and so we ask the question for every single remaining bill we have, by subtracting that bill
// out of the price question we are dealing with.
// and if price goes negative, then we have reached a possible solution
// and if price hits 0, that means 0 overshoot :D

// ill figure this out tmrw fosho u got this!
// yas okay its tomorrow lets do this

// i need to make a function that is called whatIsTheBestSolutionToPrice(int price) 
// and it needs to return a solution vector<int> which is the best list of bills 
// (best combination of bills for that input price)
// Now if a value is already stored in the array answerkey (array of vector<int>)
  // then just take that value and return it
// otherwise, just win lol
// aka do the actual calculation!
  // take the price, and recursively ask for the answer with the same price but with less 

  // but what if we dont have a duplicate bill...?
// should we store data on a solution but not using bill x? 
// or maybe if we already used bill x for the best solution for (price - x),
// then we skip that price combination..?
// 


// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp
