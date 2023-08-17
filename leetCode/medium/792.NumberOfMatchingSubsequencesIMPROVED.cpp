// new approach: for each character, have a list
// of all the words that are waiting for it.

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {

        int counter = 0;

        vector<int> wordsWaitingForCharacter[26]; // 26 letters in alphabet
        vector<int> wordCharPointers(words.size(), 0); // size, initial value
        // every word's char pointer should be 0

        // put every word in the wordsWaitingForCharacter array (based on first char)
        for (int i = 0; i < words.size(); i++) {

            string word = words[i];
            wordsWaitingForCharacter[word[0]-'a'].push_back(i);

        }
        
        // for every character, push the pointer of 
        // the words that are waiting for that character
        for (char c : s) {
            // get all the words waiting
            vector<int> wordsIndeces = wordsWaitingForCharacter[c-'a'];
            // dont forget to clear all the words waiting
            wordsWaitingForCharacter[c-'a'].clear();

            for (int index : wordsIndeces) {
                int currentCharIndex = wordCharPointers[index];
                // index is word index in words
                if (currentCharIndex + 1 == words[index].length()) {
                    // this word has been completed
                    counter++;
                }
                else {
                    // word is not completed

                    // update the char pointer of that word
                    wordCharPointers[index]++;

                    // get the next character in that word
                    char nextChar = words[index][wordCharPointers[index]];

                    // put the index of this word in the correct 
                    // 'words waiting for character'
                    wordsWaitingForCharacter[nextChar-'a'].push_back(index);

                }
            }
        }

        return counter;

    }
};