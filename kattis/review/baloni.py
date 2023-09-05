N = int(input())

heights = input().split()

for i in range(N):
    heights[i] = int(heights[i])

# keep track of all the currently flying arrows
arrowHeights = []

totalArrows = 0

# for every balloon, make sure it is popped by an arrow
# if its not, then create a new arrow to pop it
for balloonHeight in heights:

    if balloonHeight in arrowHeights:
        arrowIndex = arrowHeights.index(balloonHeight)
        arrowHeights[arrowIndex] -= 1

        # if the arrow hits the ground (below all possible balloon heights), remove it
        if (arrowHeights[arrowIndex] < 1):
            arrowHeights.remove(arrowHeights[arrowIndex])
    
    else:
        # otherwise, balloon height is not in arrow heights
        # so create a new arrow
        arrowHeights.append(balloonHeight-1)
        totalArrows += 1

print(totalArrows)





