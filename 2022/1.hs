{-# LANGUAGE OverloadedStrings #-}
import Data.List
import qualified Data.Text as T

readInt :: String -> Int
readInt = read

removeEmptyStrings :: [T.Text] -> [T.Text]
removeEmptyStrings xs = filter (\x -> x /= "") xs

splitElfSnacks :: [T.Text] -> [[T.Text]]
splitElfSnacks = map (\x -> removeEmptyStrings $ T.splitOn (T.pack "\n") x)

splitOnElves :: String -> [T.Text]
splitOnElves xs = T.splitOn (T.pack "\n\n") (T.pack xs)

sumSnacks :: [[T.Text]] -> [Int]
sumSnacks = map (\x -> sum $ map (\y -> readInt (T.unpack y)) x)

main :: IO ()
main = do
    contents <- readFile "1.txt"
    let sums = sumSnacks $ splitElfSnacks $ splitOnElves contents
    print $ maximum $ sums
    print $ sum $ take 3 $ reverse $ sort $ sums

