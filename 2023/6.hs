import Data.Char (isDigit)
import Data.List (transpose)

nonDigit :: Char -> Bool
nonDigit = not . isDigit

extractNumbers :: String -> [Int]
extractNumbers [] = []
extractNumbers xs = do
    -- could use `words` func to split?
    let afterDroppingNonDigits = dropWhile nonDigit xs
    let num = takeWhile isDigit afterDroppingNonDigits
    let afterDroppingNumber = dropWhile isDigit afterDroppingNonDigits
    if num == [] then []
    else [read num :: Int] ++ extractNumbers afterDroppingNumber

extractDigits :: String -> String
extractDigits [] = []
extractDigits xs = do
    if isDigit $ head xs then [head xs] ++ (extractDigits $ tail xs)
    else extractDigits $ tail xs

-- TODO: This could be sped up a lot; OEIS possible, or halving the time short of that, something like (but not quite):
-- (*) 2 $ length $ filter (\hold -> hold * (dist - hold) > goal) [0..(dist `div` 2)]
countPossiblePasses :: [Int] -> Int
countPossiblePasses [dist, goal] =
    length $ filter (\hold -> hold * (dist - hold) > goal) [0..dist]

solve :: [[Int]] -> Int
solve = foldr (*) 1 . map countPossiblePasses

solvePart1 :: [String] -> Int
solvePart1 = solve . transpose . map extractNumbers

solvePart2 :: [String] -> Int
solvePart2 xs =
    solve $ [map (\e -> read (extractDigits e) :: Int) xs]

main :: IO ()
main = do
    contents <- readFile "6.txt"
    let lns = lines contents
    print $ solvePart1 lns
    print $ solvePart2 lns
