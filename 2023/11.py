def rotate(m):
    return list(zip(*m[::-1]))

def expand(grid):
    bigger = []

    for i, x in enumerate(grid):
        if "." * len(x) == "".join(x):
            bigger.append(x[:])

        bigger.append(x[:])

    return bigger


def dist(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

with open("11.txt") as f:
    grid = [list(x.strip()) for x in f.readlines()]

grid = rotate(rotate(rotate(expand(rotate(expand(grid))))))
locations = []

for y, row in enumerate(grid):
    for x, cell in enumerate(row):
        if cell == "#":
            locations.append((y, x))

total_dists = 0

for i, a in enumerate(locations):
    for b in locations[i+1:]:
        total_dists += dist(a, b)

print(total_dists)
