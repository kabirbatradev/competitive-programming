class Solution {
public:
    string answerString(string word, int numFriends) {

        if (numFriends == 1) return word; // special case

        // first find the biggest letter
        // and find all occurences of that letter where the word could start

        char biggestStartingLetter = word[0];

        unordered_set<int> wordStart; // index of start of word
        int safeKeepingIndex = 0;

        wordStart.insert(0);
        
        for (int i = 1; i < word.size(); i++) {
            if (word[i] > biggestStartingLetter) {
                biggestStartingLetter = word[i]; // update biggest letter
                wordStart.clear();
                wordStart.insert(i);
                safeKeepingIndex = i;
            }
            else if (word[i] == biggestStartingLetter) {
                // wordStart.push_back(i);
                wordStart.insert(i);
                safeKeepingIndex = i;
            }
        }

        // now follow each wordStart to see which one creates the biggest word
        // and make sure theres enough space for letters
        int k = 1;
        // safekeeping word index is stored in safeKeepingIndex
        // Q: how do we account for words running out of space?
            // every word has the same max length: word.size() - (numFriends-1)
            // a word is cut off if it reaches the end of word.size()
                // if index + k == word.size(); 
        int maxWordLength = word.size() - (numFriends-1);
        while (true) {

            // if there is only one word left, that is the solution, and it should be stored in safekeeping
            if (wordStart.size() == 1) {
                // return substring from safeKeepingIndex to word size
                int length = maxWordLength;
                if (safeKeepingIndex + length > word.size()) {
                    length = word.size() - safeKeepingIndex;
                }
                return word.substr(safeKeepingIndex, length);
            }

            
            // compare for the largest next letter
            char largestNextLetter = 'a' - 1; // basically a minimum value
            unordered_set<int> bestWordStarts;
            
            for (int index : wordStart) {
                if (index + k == word.size()) {
                    // if the index is out of bounds, this word is worse than all other considerations
                    continue; // do not add to bestWordStarts
                }
                if (k == maxWordLength) {
                    // cannot add more letters... just use this word index and return! with max length
                    return word.substr(index, maxWordLength);
                    
                }
                if (word[index + k] > largestNextLetter) {
                    bestWordStarts.clear(); // clear to lose track of previous words with worse next letter
                    bestWordStarts.insert(index);
                    largestNextLetter = word[index + k]; // update largest next letter
                    safeKeepingIndex = index;
                }
                // multiple words with same next letter
                else if (word[index + k] == largestNextLetter) {
                    bestWordStarts.insert(index);
                    safeKeepingIndex = index;
                }
                // otherwise this word's next letter is than the other words
                continue;
            }

            wordStart = bestWordStarts; // update wordStart with new list
            k++;
        }

        // should never get here
        return "";
        
    }
};