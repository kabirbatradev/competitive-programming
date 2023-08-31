
from math import pi

while True:
	
	inputs = input().split()

	r = float(inputs[0])
	m = float(inputs[1])
	c = float(inputs[2])

	if (r == 0 and m == 0 and c == 0):
		break
	
	calculatedArea = c / m * 2*r*2*r
	calculatedArea = str(calculatedArea)

	# print(calculatedArea[-2:])
	if (calculatedArea[-2:] == ".0"):
		# print('yes')
		calculatedArea = calculatedArea[0:-2]

	print(pi * r * r, calculatedArea)


# print(pi)