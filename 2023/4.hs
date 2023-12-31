{-# LANGUAGE OverloadedStrings #-}

import qualified Data.Text as T
import Data.Char (isDigit)

nonDigit :: Char -> Bool
nonDigit = not . isDigit

extractNumbers :: String -> [Int]
extractNumbers [] = []
extractNumbers xs = do
    let afterDroppingNonDigits = dropWhile nonDigit xs
    let num = takeWhile isDigit afterDroppingNonDigits
    let afterDroppingNumber = dropWhile isDigit afterDroppingNonDigits
    if num == [] then []
    else [read num :: Int] ++ extractNumbers afterDroppingNumber

split :: String -> String -> [String]
split sep = map T.unpack . T.splitOn (T.pack sep) . T.pack

countMatches :: [[Int]] -> Int
countMatches (xs:ys:_) =
    sum $ map (\e -> if e `elem` ys then 1 else 0) xs

raiseToValue :: Int -> Int
raiseToValue x = if x > 0 then 2 ^ (x - 1) else 0

processLine :: String -> Int
processLine =
    countMatches .
    map extractNumbers .
    split "|" .
    head .
    drop 1 .
    split ":"

solvePart1 :: [String] -> Int
solvePart1 = sum . map raiseToValue . map processLine

increment xs i =
    take i xs ++ [1 + (xs!!i)] ++ drop (i + 1) xs

accumulateCardValues counts val i =
    map (\(e, j) -> if j > i && j <= i + val then e + 1 + (counts!!i) else e)
        $ zip (increment counts i) [0..]

solvePart2 :: [String] -> Int
solvePart2 lines = do
    let cardValues = map processLine lines
    let cardCounts = replicate (length cardValues) 0
    sum $ foldl (\a (e, i) -> accumulateCardValues a e i) cardCounts $
        zip cardValues [0..]

main :: IO ()
main = do
    contents <- readFile "4.txt"
    print $ solvePart1 $ lines contents
    print $ solvePart2 $ lines contents
