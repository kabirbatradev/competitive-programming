struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  // bool value = false; // visited value
  int index;
  Node(Node* prev, int i) : prev(prev), index(i) { }
};

class Solution {
public:

  void removeFromLinkedList(Node* &node) {
      if (node == nullptr) return;
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
      node = nullptr;
  }

  bool canFunction(
      int threshold, 
      vector<double>& thetas, 
      unordered_map<double, pair<int,int>>& m
  ) {
      int n = thetas.size();

      // what if instead of trying all i, we marked some as visited
      // vector<bool> visited(n, false);
      // linkedlist visited system?
      vector<Node*> mapping; // index to linked list node
      mapping.reserve(n);
      Node* head = new Node(nullptr, 0);
      Node* prev = head;
      for (int i = 0; i < n; i++) {
          Node* n = new Node(prev, i);
          prev->next = n;
          mapping.push_back(n);
          prev = n;
      }
      // wrap back to head to close linkedlist: 
      prev->next = head; head->prev = prev;
      // now, visited is linkedlist
      // if visited, then remove from linkedlist! (and delete)
      // use removeFromLinkedList function on mapping[i]
      // and instead of iterating i through n, check next of linkedlist

      while(head->next != head) {
          int i = head->next->index;
      // for (int i = 0; i < n; i++) { 
          // if (visited[i]) continue;
          // visited[i] = true;
          removeFromLinkedList(mapping[i]);
          // i is starting theta

          int pointsCounter = 1; // goal is k
          // start with 1 because include i itself

          int left = i-1;
          int right = i+1;

          pair<int,int> leftMost = m[thetas[i]];
          pair<int,int> rightMost = m[thetas[i]];

          // make left and right valid:
          if (left < 0) left = n-1;
          if (right == n) right = 0;

          // stop if a pointer wraps around and hits the other pointer
          while (left != right) {
              // cout << "start of loop" << endl;

              // pick whichever number is closer to leftmost or rightmost
              auto leftPoint = m[thetas[left]];
              auto rightPoint = m[thetas[right]];
              int dleft = dist(leftPoint, leftMost);
              int dright = dist(rightPoint, rightMost);

              // cout << "dleft: " << dleft << endl;
              // cout << "dright: " << dright << endl;
              // cout << endl;

              // operate on left
              if (dleft < dright) {
                  // cout << "choosing left" << endl;
                  // doesnt meet the threshold
                  if (dleft < threshold) {
                      left--;
                      // continue;
                  }
                  else {
                      // cout << "we like this point" << endl;
                      // visited[left] = true; // dont start another iteration from this point
                      removeFromLinkedList(mapping[left]);
                      left--;
                      pointsCounter++;
                      // cout << "points counter: " << pointsCounter << endl;
                      leftMost = leftPoint; // update leftmost
                      if (pointsCounter == k) return true; // we alr have enough points
                      
                  
                  }
              }
              // operate on right
              else {
                  // cout << "choosing right" << endl;
                  if (dright < threshold) {
                      right++;
                      // continue;
                  }
                  else {
                      // cout << "we like this point" << endl;
                      // visited[right] = true; // dont start another iteration from this point
                      removeFromLinkedList(mapping[right]);
                      // we like this point
                      right++;
                      pointsCounter++;
                      // cout << "points counter: " << pointsCounter << endl;
                      rightMost = rightPoint; // update rightmost
                      if (pointsCounter == k) return true; // we alr have enough points
                  }
              }
              // make left and right valid:
              if (left < 0) left = n-1;
              if (right == n) right = 0;
          }

          // now that left and right match, we should consider that number itself too!
          // do one more iteration copy paste:

              // cout << "one more interation!" << endl;

              // pick whichever number is closer to leftmost or rightmost
              auto leftPoint = m[thetas[left]];
              auto rightPoint = m[thetas[right]];
              int dleft = dist(leftPoint, leftMost);
              int dright = dist(rightPoint, rightMost);

              // cout << "dleft: " << dleft << endl;
              // cout << "dright: " << dright << endl;
              // cout << endl;

              // operate on left
              if (dleft < dright) {
                  // cout << "choosing left" << endl;
                  // doesnt meet the threshold
                  if (dleft < threshold) {
                      left--;
                      // continue;
                  }
                  else {
                      // cout << "we like this point" << endl;
                      // visited[left] = true; // dont start another iteration from this point
                      removeFromLinkedList(mapping[left]);
                      left--;
                      pointsCounter++;
                      // cout << "points counter: " << pointsCounter << endl;
                      leftMost = leftPoint; // update leftmost
                      if (pointsCounter == k) return true; // we alr have enough points
                  }
              }
              // operate on right
              else {
                  // cout << "choosing right" << endl;
                  if (dright < threshold) {
                      right++;
                      // continue;
                  }
                  else {
                      // cout << "we like this point" << endl;
                      // we like this point
                      // visited[right] = true; // dont start another iteration from this point
                      removeFromLinkedList(mapping[right]);
                      right++;
                      pointsCounter++;
                      // cout << "points counter: " << pointsCounter << endl;
                      rightMost = rightPoint; // update rightmost
                      if (pointsCounter == k) return true; // we alr have enough points
                  }
              }
              // make left and right valid:
              if (left < 0) left = n-1;
              if (right == n) right = 0;

                      

          // if we got here then we could not do the points...
          // but we could try starting at different start pos

          
      }
      // tried every starting position
      return false;
  }

  int dist(pair<int, int> a, pair<int, int> b) {
      return abs(a.first - b.first) + abs(a.second - b.second);
  }
  int k;
  int maxDistance(int side, vector<vector<int>>& points, int k) {
      this->k = k;
      // convert back from angle to point
      unordered_map<double, pair<int,int>> m;

      // convert points into angles theta and sort
      vector<double> thetas(points.size());
      for (int i = 0; i < points.size(); i++) {
          // vector<int>& point : points
          int x = points[i][0];
          int y = points[i][1];
          thetas[i] = atan2(y - side/2., x - side/2.); // shift by size/2 to center the square
          // cout << "atan2: " << thetas[i] << endl;

          m[thetas[i]] = make_pair(x, y);
      }
      
      // cout << "-----" << endl;

      sort(thetas.begin(), thetas.end());

      // print the sorted thetas
      // for (int i = 0; i < thetas.size(); i++) {
      //     cout << "theta: " << thetas[i] << endl;
      //     auto p = m[thetas[i]];
      //     cout << "point: " << p.first << " " << p.second << endl;
      //     cout << endl;
      // }
      

      int low = 0;
      int high = side*2; // side*4 overflow max side is 10^9
      int bestSuccess = low;
      while (low <= high) {
          int mid = low + (high - low) / 2;
          // cout << "NEW THRESHOLD: " << mid << endl;
          if (canFunction(mid, thetas, m)) {
              // cout << "SUCCESS" << endl;
              // this min distance is possible, so try bigger
              low = mid+1;
              bestSuccess = mid;
          }
          else {
              // cout << "FAIL" << endl;
              high = mid-1;
              
          }
      //         int threshold, 
      // vector<double>& thetas, 
      // unordered_map<theta, pair<int,int>>& m
      }
      return bestSuccess;




      
      // minimum Manhattan distance between any two points is maximized:
      // the closest 2 points should be as far as possible
      // like BSTA?

      // can function:
      /* 
      can you select points out of the set of points
      such that the manhattan distance 
      between every pair > "max allowed distance"

      brute force can function: 
      try every combination of k points
      for every pair of the k points selected, check distance
      see if that distance fits under the "max allowed"

      optimization: 
      when trying every combination of k points, we are using backtracking
      what if points were sorted such that same side are in a row?
      then we could skip points close to each other
      and we could greedily pick points that the closest but outside of the distance?

      try to do greedy:
      sort all the points into a loop, where (0, 0) is 0, and size,size is 2*size, 
      and 0 = 4*size
      kind of like a circle... 

      start with some point, and greedily pick points that are close 
      but pass the threshold distance (go left and right)

      but then we would have to start with every point? reminds me of houserobber circular lol
      issue: we dont know if the point we are starting with is an optimal point to begin with

      solution brute force: try starting at every point, and perform this greedy idea: 
      runtime = n^2 for n = num points... should be fine



      rewriting solution: 
      sort points: 
      convert xy into just a number like theta but for a square
      theta = angle from center (draw triangle and do inverse tangent y/x)
      can easily convert back to xy using "raycast": 
      do tangent of angle, and then...
      or just store a mapping between theta and the original point
      
      try starting at every point/theta, and perform this greedy idea: 
      greedily pick points that are close 
      but pass the threshold distance (go left and right in array of sorted thetas)
      if next theta is too close (convert back to point and check distance)
      then skip

      how do we cross over the 0/360 degree mark?
      if comparing 181 degrees to 0, we should actually get 179, not 181
      so just convert 0 to 360 and get the smaller abs distance
      what about 270 vs 90 or something?
      add 360 to smaller number to get an idea from the other direction! 

      so now we have sorted array of thetas:
      oh we dont even need to do conversion because:
      4, 50, 220
      if checking 220, just check left or loop around to right and check that point
      
      
      
      */

      
  }
};