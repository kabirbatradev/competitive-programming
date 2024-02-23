class Solution:
    def splitString(self, s: str) -> bool:

        def dfs(nextNum, start):
            if (start == len(s)): return True
            for i in range(start, len(s)):
                # start to i inclusive
                substring = s[start:i+1]
                num = int(substring)
                print(num)
                if (num == nextNum and dfs(num-1, i+1)):
                    return True
            return False

        for i in range(len(s) -1):
            # 0 to i inclusive
            substring = s[0:i+1]
            num = int(substring)
            print(num)
            if (dfs(num-1, i+1)):
                return True
        return False

        