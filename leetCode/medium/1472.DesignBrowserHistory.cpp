class BrowserHistory {
public:
    int index = -1; // stores which url we are currently at
    vector<string> history;

    BrowserHistory(string homepage) {
        visit(homepage);
    }
    
    void visit(string url) {

        // if we are in the middle of the history,
        // delete the history after that

        // do not delete at index, but do everything after
        if (index < history.size()-1)
            history.erase(
                history.begin() + index+1, 
                history.end()
            );
        
        // add to history
        history.push_back(url);
        index = (int)history.size()-1;
    }
    
    string back(int steps) {
        index -= steps;
        if (index < 0) index = 0;

        return history.at(index);

    }
    
    string forward(int steps) {
        index += steps;
        if (index >= history.size()) index = history.size()-1;

        return history.at(index);
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */