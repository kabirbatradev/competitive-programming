class Solution {
public:
    string s;
    string p;
    map<pair<int, int>, bool> cache;
    bool isMatch(string S, string P) {
        s = S;
        p = P;
        // i made them global so i dont need to type them every time lol

        return isMatchDP(0, 0);
    }

    // i and j are pointers to the start of the remaining substring
    bool isMatchDP(int i, int j) {
        // check if already in cache
        if (cache.count(make_pair(i, j))) {
            return cache[make_pair(i, j)];
        }


        // out of bounds edge cases
        // string is done being matched
        if (i == s.length()) {
            if (j == p.length()) {
                cache[make_pair(i, j)] = true;
                return true;
            }

            // otherwise only a match if remaining chars in p are _*
            // if not the case, then return false now
            if (j+1 == p.length() || p[j+1] != '*') {
                // if next is not *, then 
                cache[make_pair(i, j)] = false;
                return false;
            }
        }
        // matching pattern is out of bounds but we still have more of the actual string
        if (j == p.length()) {
            // pattern did not match the whole string
            cache[make_pair(i, j)] = false;
            return false;
        }

        // making sure that next char is not a *
        if (j+1 == p.length() || p[j+1] != '*') {

            // not a special char
            if (p[j] != '.' && p[j] != '*') {
                if (s[i] == p[j]) {
                    // characters match, so continue
                    // i++;
                    // j++;
                    // continue;
                    return isMatchDP(i+1, j+1);
                }
                else {
                    // characters do not match, so return false
                    cache[make_pair(i, j)] = false;
                    return false;
                }
            }
            if (p[j] == '.') {
                // just match anyway then
                // i++;
                // j++;
                // continue;
                return isMatchDP(i+1, j+1);
            }
            // is this case possible? or already handled? (it should be impossible)
            if (p[j] == '*') {
            }

        }
        else {
            // next char is *

            // if just a character, then try to match every number of it
            if (p[j] != '.') {
                // -1th case: match nothing: 
                // match the rest of the string with the rest of the pattern excluding 
                // current and *
                if (isMatchDP(i, j+2)) {
                    cache[make_pair(i, j)] = true;
                    return true;
                }

                for (int k = 0; ; k++) {

                    // try matching the next char in s
                    // i + k
                    if (i + k == s.length()) break;
                    if (s[i + k] != p[j]) break;

                    // they match, so call isMatch
                    // i+k was the last character we matched, so it should not be included in the substring
                    if (isMatchDP(i+k+1, j+2)) {
                        cache[make_pair(i, j)] = true;
                        return true;
                    }
                }

                // note: if everything failed, then return false
                cache[make_pair(i, j)] = false;
                return false;
            }
            else {
                // current is '.'

                // same idea, but no matching required
                if (isMatchDP(i, j+2)) {
                    cache[make_pair(i, j)] = true;
                    return true;
                }
                // if (isMatch(s.substr(i), p.substr(j+2))) return true;
                for (int k = 0; ; k++) {
                    if (i + k == s.length()) break;
                    // match . with the i+kth char
                    if (isMatchDP(i+k+1, j+2)) {
                        cache[make_pair(i, j)] = true;
                        return true;
                    }
                    // if (isMatch(s.substr(i+k + 1), p.substr(j+2))) return true;
                }
                cache[make_pair(i, j)] = false;
                return false; // dont forget 
            }

        }

        // shouldnt be possible
        return false;
        
    }
};

/*
modified idea:
no longer use pointers
always call isMatch again and use cache
to get around reusing memory, we can store the strings globally and keep track of position
*/

/*
class Solution {
public:
    bool isMatch(string s, string p) {

        // is caching required? will it even make things faster? 
        // I am not calling isMatch if there is no branching...
        // if I called it every time instead of incrementing pointers, would it use a lot more memory?

        int i = 0; 
        int j = 0;

        while (true) {
            // out of bounds edge cases
            // string is done being matched
            if (i == s.length()) {
                if (j == p.length()) return true;

                // otherwise only a match if remaining chars in p are _*
                // if not the case, then return false now
                if (j+1 == p.length() || p[j+1] != '*') {
                    // if next is not *, then 
                    return false;
                }
            }
            // matching pattern is out of bounds but we still have more of the actual string
            if (j == p.length()) {
                // pattern did not match the whole string
                return false;
            }

            // making sure that next char is not a *
            if (j+1 == p.length() || p[j+1] != '*') {

                // not a special char
                if (p[j] != '.' && p[j] != '*') {
                    if (s[i] == p[j]) {
                        // characters match, so continue
                        i++;
                        j++;
                        continue;
                    }
                    else {
                        // characters do not match, so return false
                        return false;
                    }
                }
                if (p[j] == '.') {
                    // just match anyway then
                    i++;
                    j++;
                    continue;
                }
                // is this case possible? or already handled (it should be impossible)
                if (p[j] == '*') {
                }

            }
            else {
                // next char is *

                // if just a character, then try to match every number of it
                if (p[j] != '.') {
                    // -1th case: match nothing: 
                    // match the rest of the string with the rest of the pattern excluding 
                    // current and *
                    if (isMatch(s.substr(i), p.substr(j+2))) return true;

                    for (int k = 0; ; k++) {

                        // try matching the next char in s
                        // i + k
                        if (i + k == s.length()) break;
                        if (s[i + k] != p[j]) break;

                        // they match, so call isMatch
                        // i+k was the last character we matched, so it should not be included in the substring
                        if (isMatch(s.substr(i+k + 1), p.substr(j+2))) return true;
                    }

                    // note: if everything failed, then return false
                    return false;
                }
                else {
                    // current is '.'

                    // same idea, but no matching required
                    if (isMatch(s.substr(i), p.substr(j+2))) return true;
                    for (int k = 0; ; k++) {
                        if (i + k == s.length()) break;
                        // match . with the i+kth char
                        if (isMatch(s.substr(i+k + 1), p.substr(j+2))) return true;
                    }
                    return false; // dont forget 
                }

            }

        }

        return false; // should never get here
        
    }
};
*/

/*
p is the pattern
idea: go through s and p together
    match characters until future char is '*'
    if '.', then guaranteed match
    if next is *, then we need to branch out and consider matching 0 or more:
        for current char not '.' aka _*: 
            try matching 0, 1, 2 chars, etc until no longer matches or out of bounds
            for each, call the isMatch function with the remaining substring
        for current char is '.' aka .*:
            guarnateed match 0 1 2 chars ... until the end of the string i guess?
            for each, call the isMatch function with the remaining substring
    note: for repeated calls to isMatch with same input can be sped up with caching
        cache map can take in pair of strings, or just concat s and p with a space between

*/