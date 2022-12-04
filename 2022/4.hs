import qualified Data.Text as T

readInt :: T.Text -> Int
readInt x = read (T.unpack x) :: Int

splitRange :: T.Text -> [T.Text]
splitRange = T.splitOn (T.pack "-")

parseRange :: T.Text -> [Int]
parseRange = map readInt . splitRange

parseRanges :: [T.Text] -> [[Int]]
parseRanges = map parseRange

splitPairs :: String -> [T.Text]
splitPairs = T.splitOn (T.pack ",") . T.pack

parsePairs :: String -> [[[Int]]]
parsePairs = map parseRanges . map splitPairs . lines

containedFully :: [[Int]] -> Bool
containedFully (x:y:_) =
    head x >= head y && tail x <= tail y ||
    head y >= head x && tail y <= tail x

overlapAtAll :: [[Int]] -> Bool
overlapAtAll (x:y:_) =
    (head $ tail x) >= head y && head x <= (head $ tail y)

main :: IO ()
main = do
    contents <- readFile "4.txt"
    let pairs = parsePairs contents
    print . length . filter containedFully $ pairs
    print . length . filter overlapAtAll $ pairs

