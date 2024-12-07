toInt :: String -> Int
toInt xs = read xs

isTolerable :: (Int, Int) -> Bool
isTolerable (x,y) = x - y > 0 && x - y < 4

validate :: [Int] -> Bool
validate report =
    (all isTolerable $ zip report (tail report)) ||
    (all isTolerable $ zip (tail report) report)

dropI :: [Int] -> Int -> [Int]
dropI xs i = take i xs ++ drop (i + 1) xs

validateWithTolerance :: [[Int]] -> [[Int]]
validateWithTolerance =
    filter (\x -> any (\(y,i) -> validate $ dropI y i) $
        zip (replicate (length x) x) [0..])

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let grid = map (\x -> map toInt $ words x) $ lines contents

    -- 1
    print $ length $ filter validate grid

    -- 2
    print $ length $ validateWithTolerance grid
