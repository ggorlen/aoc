# part 1
with open("9.txt") as f:
    lines = [list(map(int, x.split())) for x in f.readlines()]

total = 0

for line in lines:
    while any(line):
        total += line[-1]
        line = [line[i+1] - line[i] for i in range(len(line) - 1)]

print(total)

# part 2
total = 0

for line in lines:
    firsts = []

    while any(line):
        firsts.append(line[0])
        line = [line[i+1] - line[i] for i in range(len(line) - 1)]

    curr = 0

    for x in reversed(firsts):
        curr = x - curr

    total += curr

print(total)
