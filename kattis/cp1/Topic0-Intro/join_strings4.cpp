
// same as 3 but i fixed the += bug so it doesnt crash (time limit)

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

// #define PI 3.1415926535897932384626433832795


// copypasted linkedlist definition
struct node
{
    int data;
    node *next;
};

class linked_list
{
// private:
    // node *head, *tail;
public:
    node *head, *tail; 
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
};




int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // cout.precision(10);

    int numStrings; 
    cin >> numStrings;

    
    string strings[numStrings]; 
    linked_list aliases; 
    int counters[numStrings]; // keeps track of how many strings come after


    for (int t = 0; t < numStrings; t++) {
        cin >> strings[t];
        aliases.add_node(t);
        counters[t] = 0;
    }

    // cout << "\ninitial position" << endl;
    // node *current = aliases.head;
    // while (true) {
    //     cout << strings[current->data] + " ";

    //     if (current == aliases.tail) {
    //         break;
    //     }

    //     current = current->next;
    // }
    // cout << endl;


    // get all the operations
    for (int t = 0; t < numStrings - 1; t++) {
        // cout << "t = " << t << endl;
        int a, b;
        cin >> a;
        cin >> b;
        a--; b--;

        // find the chain at position a, find the chain at position b
        // move the chain at position b after the chain at position a

        node *aNode = nullptr, *bNode = nullptr, *beforeB = nullptr;
        node *currentNode = aliases.head;
        while (true) {            
            if (currentNode->data == a) {
                aNode = currentNode;
            }
            if (currentNode->data == b) {
                bNode = currentNode;
            } else {
                if (bNode == nullptr)
                    beforeB = currentNode; // if the first node is B, then before b is nullptr
            }
            if (aNode != nullptr && bNode != nullptr) {
                break;
            }
            currentNode = currentNode->next;
        }

        // cout << "a: " << strings[aNode->data] << endl;
        // cout << "b: " << strings[bNode->data] << endl;

        node *aChainTail, *bChainTail;
        aChainTail = aNode;
        for (int i = 0; i < counters[a]; i++) {
            aChainTail = aChainTail->next;
        }
        bChainTail = bNode;
        for (int i = 0; i < counters[b]; i++) {
            bChainTail = bChainTail->next;
        }

        
        // if b chain is at the end
            // if it stays in the end because a chain is at the end before b, then the end of b chain should be tail
            // if b moves somewhere to the front, then the node before b should be the tail
            
            // essentially, the node before b should be the tail
            // if the node before b is the end of the a chain, then set the tail to the end of the b chain
        
        // if a chain is at the start, then a should alr be head
        // a is at the start, so we dont need to worry about before a
        // after the a chain, we need to set that to the b node
        // after the b chain, we need to set that to what was after the a chain
        // if the a chain was at the end, then set the b chain to the end

        // if the b chain is at the start, then there is no before the b chain
            // if b chain is at the start, then assign the one after the end of b chain to the start (dont worry about it's next)
        // if the b chain is not at the start
            // before the b node's next needs to be set to the node after the b chain
            // if the before the b is the end of a, then dont change it
        
        
        if (aliases.tail == bChainTail) {
            if (beforeB != aChainTail) {
                aliases.tail = beforeB;
            }
            // dont change otherwise
        }

        node *afterAChain = aChainTail->next;
        node *afterBChain = bChainTail->next;
        aChainTail->next = bNode;

        if (afterAChain != bNode) {
            bChainTail->next = afterAChain;
        }
        if(aliases.tail == aChainTail) {
            aliases.tail = bChainTail;
        }

        if (aliases.head == bNode) {
            aliases.head = afterBChain;
        } else {
            if (beforeB != aChainTail) {
                beforeB->next = afterBChain;
            }
        }

        counters[a] += 1 + counters[b];


        // cout << "\nnew position" << endl;
        // node *current2 = aliases.head;
        // while (true) {
            
        //     // cout << current2->data << endl;
        //     // cout << strings[current2->data] << endl;

        //     if (current2 == aliases.tail) {
        //         break;
        //     }

        //     if (current2->next == nullptr) {
        //         cout << "null ahead!" << endl;
        //     }
        //     current2 = current2->next;
        // }
        // cout << endl;

    }


    // cout << "\nfinal position" << endl;
    node *current1 = aliases.head;
    while (true) {
        cout << strings[current1->data];

        if (current1 == aliases.tail) {
            break;
        }

        current1 = current1->next;
    }
    cout << endl;
    

    // brute force:
    // store all strings in an array
    // concatenate the strings based on the operation
    // print all the strings one by one
    // --
    // takes too much memory, guessing that some strings got very large

    // Next idea involves giving each string a unique alias, and doing all the operations
    // to those much smaller aliases. Then, we use the aliases as pointers
    // and print all the strings in the correct order. 
    // The aliases could be a vector/arraylist/linkedlist of integers.
    // When it says to put some integer after another integer, 
    // we could just move it to the position after.
    // Then, we would have to store how many strings are being kept directly after 
    // each one so that we can correctly add more strings after all of the ones
    // previous. This could be an array of integers corresponding to every index.
    // Whenever a string is added to another, it must bring all of the ones behind it,
    // so we would take the counter and add it to the counter, and we would take that many strings
    // and bring them all after. 
    // We move groups of strings by inserting them to a certain position, which is quite slow...
    // Linked lists definitely sound like the best way to go here since it is easier to insert
    // a whole chunk. 
    
    // If this idea doesn't work, then I can try storing all the strings themselves in a linkedlist
    // and then i would move all the strings around themselves instead of their aliases. 


}

// templates
// https://gist.github.com/kodekracker/e09f9d23573f117a5db0
// https://ncduy0303.github.io/Competitive-Programming/Contest%20Template/main.cpp