import System.IO

main = do
    contents <- readFile "1.txt"
    print $ compareSlidingWindow 3 (map readInt $ words contents)

-- https://stackoverflow.com/a/7867786/6243352
readInt :: String -> Int
readInt = read

-- https://stackoverflow.com/questions/12876384/grouping-a-list-into-lists-of-n-elements-in-haskell
-- TODO gives the right answer but check that it works in general
compareSlidingWindow :: Int -> [Int] -> Int
compareSlidingWindow _ [] = 0
compareSlidingWindow n lst
    | n > 0 && n < (length lst) =
        (if (sum (take n lst)) < (sum (take n (drop 1 lst))) then 1 else 0) +
        (compareSlidingWindow n (tail lst))
    | otherwise = 0

