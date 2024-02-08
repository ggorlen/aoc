def manhattan_dist(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def sum_all_pairs_distances(grid, gap):
    locations = []
    vertical_boost = 0

    for y, row in enumerate(grid):
        horizontal_boost = 0

        if all(c == "." for c in row):
            vertical_boost += gap

        for x, cell in enumerate(row):
            if all(grid[i][x] == "." for i in range(len(grid[x]))):
                horizontal_boost += gap

            if cell == "#":
                locations.append((y + vertical_boost, x + horizontal_boost))

    total_dists = 0

    for i, a in enumerate(locations):
        for b in locations[i+1:]:
            total_dists += manhattan_dist(a, b)

    return total_dists


if __name__ == "__main__":
    with open("11.txt") as f:
        grid = [x.strip() for x in f.readlines()]

    print(sum_all_pairs_distances(grid, gap=1))
    print(sum_all_pairs_distances(grid, gap=999_999))
