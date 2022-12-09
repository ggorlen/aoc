import Data.Char
import Data.Foldable (foldl')
import Data.List
import System.IO

freqCharAccum :: (Int, Char) -> [Char] -> (Int, Char)
freqCharAccum (freq, char) grp
    | (length grp) > freq = (length grp, grp!!0)
    | (length grp) == freq = (length grp, '_') -- TODO hacky
    | otherwise = (freq, char)

-- try maximumBy?
mostFrequentChar :: String -> Char
mostFrequentChar [] = error "empty string"
mostFrequentChar s =
    snd $ foldl' freqCharAccum (0, 'x') $ group $ sort s

flipBit :: Char -> Char
flipBit x = if x == '0' then '1' else '0'

binStrToInt :: String -> Int
binStrToInt [] = 0
binStrToInt (x:xs) =
    (digitToInt x) * (2 ^ (length xs)) + (binStrToInt xs)

findOxygenRating :: [String] -> Int -> String
findOxygenRating [] _ = error "empty list"
findOxygenRating [x] _ = x
findOxygenRating report i = do
    let mostFreqChr = mostFrequentChar $ map (\e -> e!!i) $ report
    let actualFreqChr = if mostFreqChr == '_' then '1' else mostFreqChr
    findOxygenRating (filter (\e -> e!!i == actualFreqChr) report) (i + 1)

-- TODO refactor totally stupid repetition..
findScrubberRating :: [String] -> Int -> String
findScrubberRating [] _ = error "empty list"
findScrubberRating [x] _ = x
findScrubberRating report i = do
    let mostFreqChr = mostFrequentChar $ map (\e -> e!!i) $ report
    let leastFreqChr = flipBit mostFreqChr
    let actualFreqChr = if mostFreqChr == '_' then '0' else leastFreqChr
    findScrubberRating (filter (\e -> e!!i == actualFreqChr) report) (i + 1)

main :: IO ()
main = do
    contents <- readFile "3.txt"
    let report = lines contents
    let oxygenRating = binStrToInt $ findOxygenRating report 0
    let scrubberRating = binStrToInt $ findScrubberRating report 0
    print $ (oxygenRating * scrubberRating)
