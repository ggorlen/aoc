import Data.Char (digitToInt)
import Data.List (transpose)

stringToDigits :: String -> [Int]
stringToDigits = map digitToInt

isVisibleFromI :: Int -> [Int] -> Bool
isVisibleFromI i xs =
    i == 0 ||
    i + 1 == length xs ||
    all (\x -> x < el) (take i xs) ||
    all (\x -> x < el) (drop (i + 1) xs)
    where el = xs!!i

visibleOnLine :: (Int, [Int]) -> [Bool]
visibleOnLine (i,line)
    | i == 0 || i == (len - 1) = replicate len True
    | otherwise = map (\i -> isVisibleFromI i line) $ [0..(len - 1)]
    where len = length line

countVisibleOnEitherDirection :: [[Bool]] -> [[Bool]] -> Int
countVisibleOnEitherDirection xs ys =
    sum $ map (\(xss,yss) -> length $ filter (\(a,b) -> a || b) (zip xss yss)) $ zip xs ys

main :: IO ()
main = do
    contents <- readFile "8.txt"
    let matrix = map stringToDigits $ lines contents
    let horizontal = map visibleOnLine $ zip [0..] matrix
    let vertical = transpose . map visibleOnLine $ zip [0..] $ transpose matrix
    print $ countVisibleOnEitherDirection horizontal vertical
