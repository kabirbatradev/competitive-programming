class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        
        // it seems we can decide greedily which airport to go next
        // we can backtrack if we run out of routes

        unordered_map<string, vector<string>> map;

        for (vector<string> ticket : tickets) {
            string from = ticket.at(0);
            string to = ticket.at(1);

            // cout << from << " " << to << endl;
            map[from].push_back(to);
        }

        // sort the destination lists lexicographically
        // by putting the &, we can actually modify the map
        for (auto& pair : map) {

            // by using the &, we can access the vector inside the map instead of making a copy
            vector<string>& destinations = pair.second;
            sort(destinations.begin(), destinations.end());

        }

        vector<string> ans = findSolution("JFK", map, tickets.size());
        ans.push_back("JFK");
        reverse(ans.begin(), ans.end());
        return ans;
    }

    vector<string> findSolution(
        string currentPos, 
        unordered_map<string, vector<string>> remainingTickets,
        int ticketsRemaining
    ) {

        // if the current location doesnt exist in tickets
        if (remainingTickets.find(currentPos) == remainingTickets.end()) {
            return vector<string>();
        }

        vector<string> destinations = remainingTickets[currentPos];
        // should destinations be a pq? or should we sort it in advance? (lets try sorting in advance)
        for (int i = 0; i < destinations.size(); i++) {

            string destination = destinations.at(i);

            // remove the ticket used from the remaining tickets
            vector<string> destinationsCopy(destinations);
            destinationsCopy.erase(destinationsCopy.begin() + i);

            remainingTickets[currentPos] = destinationsCopy;

            // find if there is a solution with the destination we decided to go to
            vector<string> potentialSolution = findSolution(destination, remainingTickets, ticketsRemaining - 1);
            if (potentialSolution.size() == ticketsRemaining - 1) {
                // if we traversed all the tickets
                potentialSolution.push_back(destination);
                return potentialSolution;
            }
        }
        // if we got here, then we did not find any solution
        return vector<string>();
    }


};