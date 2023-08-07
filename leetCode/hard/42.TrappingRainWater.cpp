class Solution {
public:
    int trap(vector<int>& height) {

        int trappedWater = 0;

        vector<int> window;
        window.push_back(height.at(0));
        for (int i = 1; i < height.size(); i++) {
            if (height.at(i) <= window.back()) {
                // if heights are getting smaller
                window.push_back(height.at(i));
            }
            else {
                // if height is bigger than window back
                // get water level using left side of window vs new height

                if (window.at(0) > height.at(i)) {
                    // if left side is higher
                    // iterate through window (not including first)
                    // skip if height is greater than water level
                    // add to total water
                    // set heights to water level
                    // add the new height to window
                    
                    // water level is shorter side = right side
                    int waterLevel = height.at(i);

                    for (int j = 1; j < window.size(); j++) {
                        if (window.at(j) > waterLevel) continue;
                        trappedWater += waterLevel - window.at(j);
                        window.at(j) = waterLevel;
                    }

                    window.push_back(height.at(i));
                }
                else {
                    // if new height is higher or same as left
                    // iterate through window (not including first)
                    // skip if height is greater than water level
                    // add to total water
                    // clear the window

                    // water level is shorter side = left side
                    int waterLevel = window.at(0);

                    for (int j = 1; j < window.size(); j++) {
                        if (window.at(j) > waterLevel) continue;
                        trappedWater += waterLevel - window.at(j);
                        // window.at(j) = waterLevel;
                    }
                    window.clear();
                    window.push_back(height.at(i));
                }

                
            }
        }

        return trappedWater;
    }
};