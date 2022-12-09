import Data.Char
import Data.Foldable (foldl')
import Data.List
import System.IO

-- use transpose per https://codereview.stackexchange.com/questions/270654/advent-of-code-2021-day-3-in-haskell
-- https://stackoverflow.com/questions/2578930/understanding-this-matrix-transposition-function-in-haskell
pivot :: [String] -> [String]
pivot lst =
    map (\c -> (map (\r -> lst!!r!!c) [0..((length lst) - 1)]))
    [0..(length (lst!!0) - 1)]

freqCharAccum :: (Int, Char) -> [Char] -> (Int, Char)
freqCharAccum (freq, char) grp =
    if (length grp) > freq
    then (length grp, grp!!0)
    else (freq, char)

-- try maximumBy?
mostFrequentChar :: String -> Char
mostFrequentChar [] = error "empty string"
mostFrequentChar s =
    snd $ foldl' freqCharAccum (0, '_') $ group $ sort s

flipBit :: Char -> Char
flipBit x = if x == '0' then '1' else '0'

binStrToInt :: String -> Int
binStrToInt [] = 0
binStrToInt (x:xs) =
    (digitToInt x) * (2 ^ (length xs)) + (binStrToInt xs)

main :: IO ()
main = do
    contents <- readFile "3.txt"
    let pivoted = pivot $ lines contents
    let gammaBin = map mostFrequentChar pivoted
    let gammaRate = binStrToInt gammaBin
    let epsilonRate = binStrToInt $ map flipBit gammaBin
    print $ gammaRate * epsilonRate
