with open("9.txt") as f:
    total = 0

    for line in f.readlines():
        line = list(map(int, line.split()))

        while any(x != 0 for x in line):
            total += line[-1]
            line = [line[i+1] - line[i] for i in range(len(line) - 1)]

    print(total)
