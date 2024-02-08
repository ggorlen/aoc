from collections import deque


with open("10.txt") as f:
    grid = [list(x.strip()) for x in f.readlines()]

for i, row in enumerate(grid):
    for j, cell in enumerate(row):
        if cell == "S":
            break
    if cell == "S":
        break

q = deque([(i, j, 0)])
furthest = 0

while q:
    y, x, steps = q.popleft()
    furthest = max(furthest, steps)
    neighbors = (0, 1), (1, 0), (-1, 0), (0, -1)

    for dx, dy in neighbors:
        xx = x + dx
        yy = y + dy

        if yy < 0 or yy >= len(grid) or xx < 0 or xx >= len(grid[yy]):
            continue

        curr = grid[y][x]
        next_ = grid[yy][xx]

        if (
            # south
            dy == 1 and curr in "S|7F" and next_ in "|JL" or
            # north
            dy == -1 and curr in "S|JL" and next_ in "|7F" or
            # west
            dx == -1 and curr in "S-7J" and next_ in "-FL" or
            # east
            dx == 1 and curr in "S-LF" and next_ in "-J7"
        ):
            q.append((yy, xx, steps + 1))

    grid[y][x] = "@"

print(furthest)
