class Solution {
public:
    const char unfilled = 'a'-1; // 'a' - 1 can be a "unfilled" value

    string word;
    // list of filled values (index, value) to allow for backtracking (undo)
    // vector<pair<int, char>> filledValues;

    // deque of F indices that havent been crossed yet
    //     can also be global, we can push backtracked F values from the front 
            // or local as a state thing
    // deque<int> currentF;
    // linkedlist of current F values
    //     also global i guess?
            // or also local
    // list of completed F values in order of completion + the index that they were marked happy
    //     so that we can backtrack at the correct index
        // or its just ignored if we handle F stuff locally

    string generateString(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        
        
        // string word(n+m-1, unfilled); 
        word = string(n+m-1, unfilled);

        // also find all Fs and put them into list of F indices
        deque<int> FIndices;

        for (int i = 0; i < str1.size(); i++) {
            if (str1[i] == 'T') {
                // have to copy the entirity of str2 into word starting at position i
                // and if theres something already there, then make sure it matches
                for (int j = 0; j < str2.size(); j++) {
                    char c = str2[j];
                    int wordIndex = i + j;
                    if (word[wordIndex] == unfilled) {
                        word[wordIndex] = c;
                    }
                    else {
                        if (word[wordIndex] != c) {
                            return ""; // the overlap does not match, so its impossible to generate valid word
                        }
                    }
                }
            }
            else {
                // must be 'F'
                FIndices.push_back(i);
            }
        }

        // now all T's are filled 

        // before doing DFS, we should check if any F are entirely mad already from the filled Ts
        // or maybe just let that be handled in dfs
        // for (int i = 0; i < str1.size(); i++) {
        //     if ()
        // }

        list<int> currentF;
        // if dfs returned false, then we should do empty string
        if (!dfs(0, FIndices, currentF, str1, str2)) {
            return "";
        }

        return word;
    }

    // return true if already obtained a valid word
    bool dfs(int wordIndex, deque<int>& FIndices, list<int>& currentF, string& str1, string& str2) {
        // base cases:
        // if we have any current F where the word index passed it+the size of the string, then its mad and return false
            // only mad if we passed index + str2.size()-1 --> if the size is 1, then 
            // bad if we passed the index itself
        if (currentF.size() > 0 and currentF.front()+str2.size()-1 < wordIndex) {
            return false; // we can just check if the first one failed bc these are in sorted order
        }
        // otherwise, if word index is at the end, then return true
        if (wordIndex == word.size()) return true;

        list<int> currentFCopy = currentF; // keep for undo before backtracking 

        // check if word index = the top f index. if so, then move that to the end of current F
        int removedFIndex = -1; // store this for undo for backtracking
        if (wordIndex == FIndices.front()) {
            removedFIndex = FIndices.front();
            currentF.push_back(FIndices.front());
            FIndices.pop_front();
        }

        // if word index is not something we can write to, then
        // check if we can get rid of some of the current F
            // check if they are happy by 
            // iterate through list of all current F
                // list contains their index where they started, 
                // so at wordIndex, we dont want
                // char to match str2[word index - current F index]
            // if they do not match, then happy and we can remove current F
                // otherwise we cannot remove
        //  then call dfs on new state
        // return false if the dfs returned false (just return that dfs)
        if (word[wordIndex] != unfilled) {
            vector<list<int>::iterator> toErase;
            for (auto it = currentF.begin(); it != currentF.end(); it++) {
                int currentFIndex = *it;
                if (word[wordIndex] != str2[wordIndex - currentFIndex]) {
                    // currentF.erase(it);
                    toErase.push_back(it);
                }
            }
            for (auto it : toErase) {
                currentF.erase(it);
            }

            if (dfs(wordIndex + 1, FIndices, currentF, str1, str2)) return true;
            // undo FIndices modification before backtracking
            if (removedFIndex != -1)
                FIndices.push_front(removedFIndex);
            currentF = currentFCopy; // undo for backtracking
            return false;
            // return dfs(wordIndex + 1, FIndices, currentF, str1, str2);
        }
        

        
        // if we can write to it 
            // iterate through every character from a to z that we could write to here
            // then do the check above about whether we can delete some current F
            // and for each char we could write, call dfs with new state
        // also write that char to word
        // and put into filledValues? or actualy we dont need to because we can just unrwrite to word if it returned false
        // and finally, we can return false if everything failed
        // cout << "unfilled at " << wordIndex << endl;
        // cout << "word currently: " << word << endl;
        for (char c = 'a'; c <= 'z'; c++) {
            word[wordIndex] = c;
            // cout << "trying word = " << word << endl;

            vector<list<int>::iterator> toErase;
            for (auto it = currentF.begin(); it != currentF.end(); it++) {
                int currentFIndex = *it;
                if (word[wordIndex] != str2[wordIndex - currentFIndex]) {
                    // currentF.erase(it);
                    toErase.push_back(it);
                }
            }
            for (auto it : toErase) {
                currentF.erase(it);
            }
            
            if (dfs(wordIndex + 1, FIndices, currentF, str1, str2)) {
                return true;
            }

            word[wordIndex] = unfilled; // reset for backtracking
            // undo FIndices modification before backtracking
            if (removedFIndex != -1)
                FIndices.push_front(removedFIndex);
            currentF = currentFCopy; // undo for backtracking
        }
        return false;
        
    }
};

/*
for every index where str1 has a T, we can copy str2 to that chunk of word starting at i
    now certain regions will be unfilled
    what if str2 is really long and overlaps with other chunks of str1?
    then we have to make sure the overlap matches
for every index where str1 has an F, that index itself may or may not be filled already...
    we can immediately check if any F's are already impossible
    and some F's are already guaranteed possible

run a dfs filling in unfilled values with 'a's and checking if the F are happy or not
if not, then we have to backtrack
the first valid filling we encounter will also be lexographically earliest. 
this dfs is similar to greedily assigning a low value, except we backtrack when there are multiple constraints on a letter 

new idea for handling multiple constraints on letters
go through all str1 'F's 
    for each letter in word, create a list of 26 bools all set to true by default
    set them to false if there was some F that said that, at that index in word,
        there cannot be that particular letter (because then it would match with str1)
    but wait, we can have matching chars as long as the entire str1 does not match
this idea was incorrect

if we actually greedily assigned chars to empty spaces, how would we know if a F is mad?
    list of F indices can be a vector or some kind of list
    F is mad if all the substring matches str2 perfectly
    F can be deleted from list if at least one character already differs
as we assign characters, we iterate forward
    if we assign something that doesnt match with the earliest F, we can delete the earliest F
    there can be overlapping Fs, so we should check if we did not match them simultaneously to be able to delete all of them
    if our index passed an F and we never deleted it, then all characters matched and we must backtrack...

any elegant way of managing Fs at the same time?
    use deque with sorted F indices
    if we are at an index where an F started, then add it to a linkedlist
    for every new char, iterate through linkedlist of current Fs 
    delete one if we placed a char that satisfies it
    if an F survived its whole journey, then its mad, and we must backtrack to change what charactesr we put in unfilled slots

how do we incorporate this idea into dfs?
    at every dfs, try setting unfilled to a letter, and call dfs with updated state
    state:
        global current 'word'
        list of filled values (index, value) to allow for backtracking (undo)
            this can also be global, where we pop front when backtracking
        deque of F indices that havent been crossed yet
            can also be global, we can push backtracked F values from the front 
        linkedlist of current F values
            also global i guess?
        list of completed F values in order of completion + the index that they were marked happy
            so that we can backtrack at the correct index
    
what if the states werent all global? easier to manage?
    much easier to write code, but now it TLE when str1 is super large and str2 is decently large
what if we just make the deque of FIndices not cloned each time bc its prob really big
*/