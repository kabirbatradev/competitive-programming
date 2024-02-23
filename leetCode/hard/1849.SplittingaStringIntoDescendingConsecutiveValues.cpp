class Solution {
 public:
  bool splitString(string s) {
    // long snum = stol("9465072333777578147");
    // doesnt work because the input number is too big; we can try catch?

    // try different lengths of digits to be the first number,
    // and see if its possible to continue

    // simple solution (less pruning): try every single length of digit for
    // remaining string

    // for every possible start number
    // s.length()-1-1 because the whole string cant be the number (has to be a
    // split somewhere)
    for (int i = 0; i < s.length() - 1; i++) {
      // extract number from 0 to i inclusive
      long num = extractNumber(s, 0, i);
      if (num == -1) continue;
      cout << num << endl;
      bool ret = dfs(s, num - 1, i + 1);
      if (ret) return true;
    }
    return false;
  }

  long extractNumber(string s, int start, int endInclusive) {
    // String TO Integer LONG

    long num = -1;
    try {
      // amount_input = stoi(input);
      num = stol(s.substr(start, endInclusive - start + 1));

    } catch (exception &err) {
      cout << "Conversion failure" << endl;
      // cin>>input;
      return -1;
    }

    // long num = stol(s.substr(start, endInclusive - start + 1));

    return num;
  }

  bool dfs(string s, long nextNum, int startIndex) {
    // base case, when theres no number left
    if (startIndex == s.length()) return true;

    // iterate thorugh all possibenl reamining nuebrs
    for (int i = 0; i < s.length() - startIndex; i++) {
      // extract number from 0 to i inclusive
      long num = extractNumber(s, startIndex, startIndex + i);
      if (num == -1) continue;
      cout << num << endl;
      if (num == nextNum) {
        bool ret = dfs(s, nextNum - 1, startIndex + i + 1);
        if (ret) return true;
      }
    }
    return false;
  }
};