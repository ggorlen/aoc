transitions = {}

with open("8.txt") as f:
    for i, ln in enumerate(f):
        line = ln.strip()

        if i == 0:
            instructions = [1 if x == "R" else 0 for x in line]
        elif line:
            k, v = line.split(" = ")
            transitions[k] = [x.strip("()") for x in v.split(", ")]

curr = "AAA"
i = 0
steps = 0

while curr != "ZZZ":
    curr = transitions[curr][instructions[i]]
    i = (i + 1) % len(instructions)
    steps += 1

print(steps)
