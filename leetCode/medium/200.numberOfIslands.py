class Solution:
    # set of tuples: (row, column)
    def numIslands(self, grid: List[List[str]]) -> int:
        # if not grid:
        #     return 0
        
        dx = [0, 0, -1, 1]
        dy = [1, -1, 0, 0]

        visitedSet = set()


        # current node is (row, column)
        def dfs(currentNode, grid):
            landOrWater = grid[currentNode[0]][currentNode[1]]
            if landOrWater == "0":
                return
            
            # if its a 1: 
            if currentNode in visitedSet:
                # already visited (skip)
                return
            
            # current node is not visited
            visitedSet.add(currentNode)

            # iterate through all possible adjacent nodes
            for i in range(4):
                newPosition = (currentNode[0] + dx[i], currentNode[1] + dy[i])

                # check if node is valid
                # if out of bounds, then continue
                if newPosition[0] < 0 or newPosition[0] >= len(grid):
                    continue
                if newPosition[1] < 0 or newPosition[1] >= len(grid[0]):
                    continue

                dfs(newPosition, grid)
            
            return

        count = 0

        for row in range(len(grid)):
            for col in range(len(grid[0])):
                position = (row, col)
                # if 1 and not visited
                if grid[row][col] == "1" and position not in visitedSet:
                    dfs(position, grid)
                    count += 1

        # dfs((0, 0), grid)

        # for element in visitedSet:
        #     print(element)

        return count
