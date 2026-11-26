# part 1
total = 0

with open("3.txt") as f:
    for line in f:
        second_digit = 0
        first_digit = 0
        first_digit_idx = 0

        for i, x in enumerate(line[:-2]):
            x = int(x)

            if x > first_digit:
                first_digit = x
                first_digit_idx = i

        for i, x in enumerate(line[first_digit_idx + 1 : -1]):
            x = int(x)

            if x > second_digit:
                second_digit = x

        total += int(f"{first_digit}{second_digit}")

print(total)


# part 2
# let's generalize the part 1 soln.
# if we need to make 2, we disregard the last element and find the first largest element.
# then we find the largest element to the right of the first.
# now for 12, we disregard the last 11 elements, find the largest element to the left. from that index, we disregard the last 10 elements, find the largest element to the left of those 10 and to the right of the one we already picked.
# repeat until complete.
# logic here is we HAVE to take those sooner or later, so base case, we have 2 length string and we take 2. if we have a 3 length string, then we need to reserve one, so we can't take the last number even if it's the biggest.
def make_largest_joltage(x, k=12):
    result = []
    start = 0
    end = len(x) - k

    for i in range(k, 0, -1):
        end += 1
        best = 0

        for j, y in enumerate(x):
            if j >= start and j < end and int(y) > best:
                best = int(y)
                start = j + 1

        result.append(best)

    return int("".join(map(str, result)))


total = 0

with open("3.txt") as f:
    for line in f:
        total += make_largest_joltage(line.strip())

print(total)
