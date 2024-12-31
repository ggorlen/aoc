-- references:
-- https://stackoverflow.com/a/20578855/6243352
-- https://hackage.haskell.org/package/containers-0.4.0.0/docs/Data-Map.html
-- https://github.com/yav/advent_of_code/blob/master/2019/P03.hs
-- alternate approach, array: https://hackage.haskell.org/package/array-0.5.8.0/docs/Data-Array.html

-- TODO cleanup/generalize

import qualified Data.Map.Strict as Map

find loc grid = Map.findWithDefault '\0' loc grid

findAll coords grid = (map (\x -> find x grid) coords) == "XMAS"

findXmasNeighbors1 (x, y) grid =
    (if findAll [(x, y), (x + 1, y), (x + 2, y), (x + 3, y)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x, y + 1), (x, y + 2), (x, y + 3)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x, y - 1), (x, y - 2), (x, y - 3)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x - 1, y), (x - 2, y), (x - 3, y)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x - 1, y - 1), (x - 2, y - 2), (x - 3, y - 3)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x + 1, y - 1), (x + 2, y - 2), (x + 3, y - 3)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x - 1, y + 1), (x - 2, y + 2), (x - 3, y + 3)] grid
        then 1 else 0) +
    (if findAll [(x, y), (x + 1, y + 1), (x + 2, y + 2), (x + 3, y + 3)] grid
        then 1 else 0)

findXmasNeighbors2 (x, y) grid =
    if ((find (x, y) grid) == 'A' &&
       (find (x + 1, y - 1) grid) == 'S' &&
       (find (x - 1, y - 1) grid) == 'M' &&
       (find (x + 1, y + 1) grid) == 'S' &&
       (find (x - 1, y + 1) grid) == 'M') ||

       ((find (x, y) grid) == 'A' &&
       (find (x + 1, y - 1) grid) == 'M' &&
       (find (x - 1, y - 1) grid) == 'S' &&
       (find (x + 1, y + 1) grid) == 'M' &&
       (find (x - 1, y + 1) grid) == 'S') || 

       ((find (x, y) grid) == 'A' &&
       (find (x + 1, y - 1) grid) == 'M' &&
       (find (x - 1, y - 1) grid) == 'M' &&
       (find (x + 1, y + 1) grid) == 'S' &&
       (find (x - 1, y + 1) grid) == 'S') ||

       ((find (x, y) grid) == 'A' &&
       (find (x + 1, y - 1) grid) == 'S' &&
       (find (x - 1, y - 1) grid) == 'S' &&
       (find (x + 1, y + 1) grid) == 'M' &&
       (find (x - 1, y + 1) grid) == 'M')
    then 1 else 0

main :: IO ()
main = do
    contents <- readFile "4.txt"

    let grid = concat $
         map (\(i, x) -> map (\(j, y) -> ((i, j), y)) $
         zip [0..] x) $
         zip [0..] $ lines contents

    let valueAtCoords = Map.fromList grid
    print $ sum $
        map (\x -> findXmasNeighbors2 x valueAtCoords) $
        map (\((x, y), _) -> (x, y)) grid

