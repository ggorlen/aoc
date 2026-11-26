import qualified Data.Text as T

isMirrored :: String -> Bool
isMirrored x = do
    let len = (length x)
    len `mod` 2 == 0 && (take (len `div` 2) x) == (drop (len `div` 2) x)

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let split = T.splitOn (T.pack ",") (T.pack $ head $ lines contents)
    let ranges = map (\e -> map (\f -> read (T.unpack f) :: Int) $ T.splitOn (T.pack "-") e) split

    -- 1
    print $ foldl (\a (start:end:_) -> a + foldl (\aa x -> if isMirrored (show x) then (x + aa) else aa) 0 [start..end]) 0 ranges
