class BrowserHistory {
public:
    vector<string> history;
    int numElements = 0;
    int insertHere = 0;

    BrowserHistory(string homepage) {
        visit(homepage);
    }
    
    void visit(string url) {
        if (insertHere == history.size()) {
            history.push_back(url);
        }
        else {
            history[insertHere] = url;
        }
        insertHere++;
        numElements = insertHere;
    }
    
    string back(int steps) {
        insertHere = max(1, insertHere - steps);
        return history[insertHere-1];
    }
    
    string forward(int steps) {
        insertHere = min(numElements, insertHere + steps);
        return history[insertHere-1];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */