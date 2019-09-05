def calc_close_knight(dx, dy, first_move):
	# first_move is true when it's the first move, false otherwise

	"""
	Solve for inner 5x5 square
	"""

	dx, dy = max(dx, dy), min(dx, dy) # Assigns dx >= dy

	if dx == 0 and dy == 0: return 0
	if dx == 1 and dy == 0: return 3 if first_move else 1
	if dx == 1 and dy == 1: return 2
	if dx == 2 and dy == 0: return 2
	if dx == 2 and dy == 1: return 1
	if dx == 2 and dy == 2: return 4 if first_move else 2

def calc_knight_moves(x1, y1, x2, y2):
	if x1 == 0 and y1 == 0 and x2 == 1 and y2 == 1 or \
		x1 == 1 and y1 == 1 and x2 == 0 and y2 == 0:
		return 4 # Special corner case, starting from (1, 1)

	dx, dy = abs(x1 - x2), abs(y1 - y2)

	return calc_knight_moves_helper(dx, dy)

def calc_knight_moves_helper(dx, dy):
	dx, dy = max(dx, dy), min(dx, dy)

	if dx <= 2: # If already in the 5x5 sqyare
		return calc_close_knight(dx, dy, True)

	ny = max((2 * dy - dx - 1) // 3, 0) # remember that negative ny's should be 0
	nx = (dx - ny - 1) // 2 # // handles flooring

	dx = dx - 2 * nx - ny
	dy = (dy - 2 * ny - nx) % 2 # python handles mathematical modulus correctly
	                            # other languages might not

	return nx + ny + calc_close_knight(dx, dy, False)

print(calc_knight_moves(510, 430, 0, 0))