import Data.List (nub)

findMarker :: Int -> String -> Int
findMarker n xs
    | (length . nub $ take n xs) == n = n
    | otherwise = 1 + findMarker n (tail xs)

main :: IO ()
main = do
    contents <- readFile "6.txt"
    print $ findMarker 4 contents
    print $ findMarker 14 contents

