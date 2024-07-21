class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {

        // all we care about are the differences, so we really only have 1 array 

        // note that if a difference is 0, then it is always better to
        // do operations on subarrays to the left and right of the 0
        // rather than to include the 0 and then have to backtrack..? i think
            // cant think of any edge cases to this rn at least

        // idk how useful my note is
        // 5 5 -5 5 5
        // push all the 5s to 0, the -5 back up to 0 from -10 = 15 moves
        // push the -5 up and push separate groups of 5 = 15 moves

        // note that there were no differences of 0, but there was a "swap"
        // in the sign of the differences
        // therefore, every swap in signs defines a new subproblem where 
        // numbers can be moved together efficiently

        // the number of moves a group takes is equal to maybe the peak of the group
        // but what if there are multiple peaks
        // if peaks are pushed down together, then the stuff in the middle overshoots
        // which is bad

        // therefore, a subproblem that is strictly rising and and then falling
        // can be solved with a minimum of the peak 

        // and if it switches from rising to falling back to rising again
        // then that is the start of a separate sub problem which may be solved
        // with its own set of moves..? 

        // but if the whole thing is all positive, then it can all move down together
        // until the point "where a switch between rising and falling happens" reaches 0


        // strictly separate subproblems: positives vs negatives (ignore 0s)

        // within a group of positives:
        // rising to falling is easy case
        // rising to falling to rising to falling:
            // split into 2 problems where "base" is the point where 
            // it switched to rising again
        // up down up down up down (bases are different)
        // the lower base is split off as its own sub problem earlier

        // how do we keep track of an "all positive subproblem":
        // vector or stack or something
        // iterate through the sub problem
        // keep track of whether rising or falling
        // idk
        // base = the first number
        // keep track of biggest number aka peak
        // if we are falling, there are 2 cases: 
            // we switch back to rising and pass the base
            // we switch back to rising before passing the base
        // pass the base: update the base value maybe.. now that it is lower
        // didnt pass the base: ig the base is the same
        // and update the counter with the difference between the base and the peak
        // now we are going up again, so we will have a new peak
        // ig same process?
        // final case is we reach the end (a 0 or a negative aka end of sub problem)
            // the new base is 0, then just do peak - base again
        
        // rethink the mutliple base situation
        // the whole point:
            // if there are multiple bases, then we dont have to do repeated computation
            // left peak and right peak share a higher base than their edges
            // move both peaks down together by the higher base's value
            // then move down the rest of the peaks separately
        // more than 2 peak case: aka multiple bases
            // 0 1 18 5 20 8 15 0
            // 18, 20, 15 are peaks
            // 5 and 8 are bases
            // work done (ignoring oerlap) = 18 + 20 + 15 
            
            // since base 5 is the lowest base, we can do 5 work on everyone
                // +5 moves
            // peaks updated to 18-5, 20-5, 15-5
            // the 18 peak is not neighboring the 8, so it can complete its work
                // + 18-5
            // the next base is 8-5 = 3 high peak
                // +3 work
            // the final 2 peaks work = 20 - 8 and 15 - 8

            // overlap = 5*2 bc 5 for everyone since 5 is the lowest base
                // 3 peaks means only do work for one peak i think...
            // then the base 8 is just a 3 while the other peaks are -5 each
                // this results in 
        
        // how would we keep track of this?
            // base = 0
            // peak = 18
            // base = 5
                // +5 base work since new base, +18-5 for the peak
            // peak = 20
            // base = 8
                // +3 base work bc new highest base, +20 - 8 work for the peak
            // peak = 15
            // base = 0
                // no new work for lower base
                // but we still update the base 
                // 15 - 8 for the peak

        // what if there were more bases and peaks? 
        // more specifically, what if we didnt go down to 0
        // and then we had another base that went up again?
            // peak = smth
            // base = new higher base
                // update latest base
                // do work for the new highest base
                // peak - current base for the new peak

        // what if a base later is higher than the peak now? is that a weird case?
            // well then the base kinda just rises and we already handled the peak now right?
        // or vise versa too: base now is higher than a peak later
            // well then the base must have dropped right? we handled that

        // all in all:
            // new base means set base
                // if the base is higher, then do work to get there from the prev base
            // new peak means peak - base
                // wait actually we do the work of peak - higher base (even if higher base is older)
                // look at the case where the new base is 0
        // thats it?



        long long operationsCounter = 0;

        int mode = 0; // negative, 0, or positive
        int base = 0;

        bool subProblemRising = true; 
        // always rising from the start because start from 0 basically
        int prevAbsoluteDifference = 0;

        int peak = 0;

        // assume there is a 0 at the end since we always look back when we hit a 0 to 
        // add computations
        nums.push_back(0);
        target.push_back(0);

        for (int i=0; i < nums.size(); i++) {
            cout << endl;
            int difference = target[i] - nums[i];
            int absoluteDifference = abs(difference);
            cout << difference << " " << absoluteDifference << endl;

            // bool positive = difference > 0;

            
            // same sign
            if ((difference > 0 && mode > 0) || (difference < 0 && mode < 0)) {
                cout << "same sign" << endl;

                // are we currently rising or falling? use prevAbsoluteValue
                bool currentlyRising = absoluteDifference - prevAbsoluteDifference > 0;
                cout << "currentlyRising = " << currentlyRising << endl;

                if (subProblemRising == currentlyRising) {
                    // if still rising or still falling, then we dont really care
                    // since we only have to do things at inflection points
                    // continue;
                }

                // otherwise, we switched from rising to falling or vice versa

                // if we went from falling to rising: new base
                else if (currentlyRising) {
                    
                    int newBase = prevAbsoluteDifference;
                    int higherBase = base;
                    // if the new base is higher, then we do some work 
                    if (newBase > base) {
                        operationsCounter += newBase - base;
                        cout << "adding new base " << newBase << " - " << base << endl;

                        higherBase = newBase;
                    }

                    // update the base 
                    base = newBase;

                    // do work for the previous peak:
                    // operationsCounter += peak - base;
                    operationsCounter += peak - higherBase;
                    cout << "adding new peak " << peak << " - " << higherBase << endl;

                    
                }
                // if we went from rising to falling: new peak
                else {
                    peak = prevAbsoluteDifference;
                }

                // should update this at the end
                // prevAbsoluteDifference = absoluteDifference;


            }
            else {
                // switched modes or mode is now 0
                cout << "switched modes or mode is now 0" << endl;


                // TODO handle case where we still havent added the operations from the latest peak
                // copy base the new base code, but the new base is just 0
                int newBase = 0;
                int higherBase = base; // always the previous base

                // if the new base is higher, then we do some work 
                // if (newBase > base) {
                //     operationsCounter += newBase - base;
                // }

                // update the base 
                // base = newBase;

                // what if the one directly before this was a peak?
                if (prevAbsoluteDifference > peak) peak = prevAbsoluteDifference;

                // do work for the previous peak
                operationsCounter += peak - higherBase;
                cout << "adding fall to 0 " << peak << " - " << higherBase << endl;
                
                // TODO reset all the variables
                subProblemRising = true; // reset 
                // prevAbsoluteDifference = 0; // this should be set to current
                peak = absoluteDifference; // should be set to the current value
                    // since we might be switching sides but need an initial peak value

                mode = difference;
                base = 0; // base should be 0 because we need to go down to 0
                // continue;
            }

            // should update this at the end
            prevAbsoluteDifference = absoluteDifference;
        }


        

        return operationsCounter;

    }
};