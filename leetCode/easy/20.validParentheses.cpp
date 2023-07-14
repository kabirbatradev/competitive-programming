class Solution {
public:
    bool isValid(string str) {

        stack<char> s; 
        for (char c : str) {
            if (c == '(' || c == '[' || c == '{') {
                s.push(c);
            }
            else {
                if (s.empty()) return false;
                char top = s.top();
                if (top == '(') {
                    if (c != ')') {
                        return false;
                    }
                }
                else if (top == '[') {
                    if (c != ']') {
                        return false;
                    }
                }
                else if (top == '{') {
                    if (c != '}') {
                        return false;
                    }
                }
                else {
                    return false;
                }
                s.pop();
                
            }
        }

        return s.empty();
        
    }
};