{-# LANGUAGE OverloadedStrings #-}
import Data.List (sort)
import qualified Data.Text as T

readInt :: String -> Int
readInt = read

nonEmpty :: T.Text -> Bool
nonEmpty x = x /= ""

splitLine :: T.Text -> [T.Text]
splitLine x = filter nonEmpty $ T.splitOn (T.pack "\n") x

splitOnElves :: String -> [T.Text]
splitOnElves x = T.splitOn (T.pack "\n\n") $ T.pack x

unpackToInt :: T.Text -> Int
unpackToInt x = readInt $ T.unpack x

sumSnack :: [T.Text] -> Int
sumSnack xs = sum $ map unpackToInt xs

main :: IO ()
main = do
    contents <- readFile "1.txt"
    let sums = map sumSnack $ map splitLine $ splitOnElves contents
    print $ maximum $ sums
    print $ sum $ take 3 $ reverse $ sort $ sums

