import Data.Foldable (foldl')
import System.IO

strToWordsPerLine :: String -> [[String]]
strToWordsPerLine s = map words $ lines s

secondToInt :: [[String]] -> [(String, Int)]
secondToInt pairs = map (\e -> ((e!!0), (read (e!!1)))) pairs

setDirection :: (String, Int) -> (String, Int)
setDirection (x, y) = if x == "up" then (x, -1 * y) else (x, y)

buildDirections :: [(String, Int)] -> [(String, Int)]
buildDirections pairs = map setDirection pairs

accumDepth :: (Int, Int) -> (String, Int) -> (Int, Int)
accumDepth (depth, aim) (direction, amount) =
    if direction == "forward"
    then (aim * amount + depth, aim)
    else (depth, aim + amount)

-- surprising opposite order: foldl: (acc, el) ; foldr: (el, acc)
computeDepth :: [(String, Int)] -> Int
computeDepth directions = fst $ foldl' accumDepth (0, 0) directions

accumHorizontalPosition :: Int -> (String, Int) -> Int
accumHorizontalPosition horizontalPosition (direction, amount) =
    if direction == "forward"
    then horizontalPosition + amount
    else horizontalPosition

computeHorizontalPosition :: [(String, Int)] -> Int
computeHorizontalPosition directions =
    foldl' accumHorizontalPosition 0 directions

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let directions = buildDirections $ secondToInt $ strToWordsPerLine contents
    print $ (computeDepth directions) * (computeHorizontalPosition directions)
