

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
    // std::ios::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
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

    cout << "\ninitialization success" << endl;

    cout << "initial position" << endl;
    node *current1 = aliases.head;
    while (true) {
        cout << strings[current1->data];

        if (current1 == aliases.tail) {
            break;
        }

        current1 = current1->next;
    }
    cout << endl;


    // get all the operations
    for (int t = 0; t < numStrings - 1; t++) {
        cout << "t = " << t << endl;
        int a, b;
        cin >> a;
        cin >> b;
        a--; b--;

        // get b, move it after a, increase counter of a

        // find a and b by iterating through the linkedlist till you find nodes that equal a and b
        node *aNode = nullptr, *bNode = nullptr, *beforeB = nullptr;
        node *currentNode = aliases.head;
        while (true) {

            cout << strings[currentNode->data] << "?" << endl;
            
            if (currentNode->data == a) {
                aNode = currentNode;
                // cout << "found node a" << endl;
            }

            if (currentNode->data == b) {
                bNode = currentNode;
                // cout << "found node b" << endl;
            } else {
                if (bNode == nullptr)
                    beforeB = currentNode; // if the first node is B, then before b is nullptr
            }

            if (aNode != nullptr && bNode != nullptr) {
                break;
            }
            // else
            currentNode = currentNode->next;
        }

        // cout << "found both a and b and broke out" << endl;
        cout << "a: " << strings[aNode->data] << endl;
        cout << "b: " << strings[bNode->data] << endl;
        if (beforeB != nullptr) {
            cout << "beforeB: " << strings[beforeB->data] << endl;
        } else {
            cout << "beforeB: null" << endl;
        }

        // move b (along with its trailing chain) after a
        node *afterA = aNode->next;
        cout << "after a is: " << ((afterA == nullptr) ? "null" : strings[afterA->data]) << endl;
        
        node *endOfAChain = aNode;
        for (int i = 0; i < counters[aNode->data]; i++) {
            endOfAChain = endOfAChain->next;
            cout << strings[endOfAChain->data] << endl;
        }
        cout << counters[aNode->data] << endl;

        node *afterEndOfAChainOriginal = endOfAChain->next;
        endOfAChain->next = bNode;
        cout << "after a's chain is now set to b: " << ((endOfAChain->next == nullptr) ? "null" : strings[endOfAChain->next->data]) << endl;
        

        node *lastOfChain = bNode;
        for (int i = 0; i < counters[b]; i++) {
            lastOfChain = lastOfChain->next;
        }

        // cout << "after end of b chain is: " << strings[lastOfChain->next->data] << endl;

        // whatever was before b, after that should be whatever was after the end of the b chain.
        // we need to find what was before b to do this....
        if (beforeB == nullptr) {
            aliases.head = lastOfChain->next;
            cout << "after end of b chain is now the head" << endl;
        } else {
            beforeB->next = lastOfChain->next;
            cout << "gap where b chain was pulled out has been closed" << endl;

        }
        
        // whatever was after a chain is now after the end of b
        // unless after a was b itself...
        if (afterEndOfAChainOriginal == bNode) {
            // then dont change the end of the b chain
        } else {
            lastOfChain->next = endOfAChain->next;
        }
        cout << "after end of b chain is now: " << ((lastOfChain->next == nullptr) ? "null" : strings[lastOfChain->next->data]) << endl;
        cout << "after a should still be b: " << ((aNode->next == nullptr) ? "null" : strings[aNode->next->data]) << endl;

        // tail should move if a chain was last
        if (endOfAChain == aliases.tail) {
            aliases.tail = lastOfChain;
        }

        // number of strings following a is now 1 + number of strings following b
        counters[a] = 1 + counters[b];


        cout << "\ncurrent position" << endl;
        node *current2 = aliases.head;
        while (true) {
            cout << strings[current2->data];

            if (current2 == aliases.tail) {
                break;
            }

            current2 = current2->next;
        }
        cout << endl;

        // strings[a] = strings[a] + strings[b];
        // strings[b] = "";

    }

    // loop through linkedlist and print respective strings
    node *current = aliases.head;
    while (true) {
        cout << strings[current->data];


        if (current == aliases.tail) {
            break;
        }
        current = current->next;

    }

    // for (string s : strings) {
    //     cout << s;
    // }
    // cout << "\n";
    

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