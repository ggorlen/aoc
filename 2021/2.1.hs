import System.IO

seconds :: [[String]] -> [String]
seconds lst = map (\e -> e!!1) lst

getDirection :: [[String]] -> String -> [[String]]
getDirection pairs direction =
    filter (\e -> (head e) == direction) pairs

mapToInt :: [String] -> [Int]
mapToInt lst =
    map (read :: String -> Int) lst

sumDirection :: [[String]] -> String -> Int
sumDirection pairs direction =
    sum $ mapToInt $ seconds $ getDirection pairs direction

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let pairs = map words $ lines contents
    let forwards = sumDirection pairs "forward"
    let ups = sumDirection pairs "up"
    let downs = sumDirection pairs "down"
    print $ forwards * (downs - ups)
