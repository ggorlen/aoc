import Data.Char (ord)
import Data.List (nub)

find :: Char -> String -> Bool
find x [] = False
find x ys
    | x == head ys = True
    | otherwise = find x $ tail ys

findDupe :: String -> [String] -> Char
findDupe x xs
    | all (\y -> find (head x) y) xs = head x
    | otherwise = findDupe (tail x) xs

valueOf :: Char -> Int
valueOf x = if o > 96 then o - 96 else o - 38
    where o = ord x

sumValues :: String -> Int
sumValues xs = sum $ map valueOf xs

chunk :: Int -> [a] -> [[a]]
chunk _ [] = []
chunk n xs = [take n xs] ++ (chunk n (drop n xs))

splitHalves :: (Int,String) -> (String,String)
splitHalves (x,y) = (nub $ take x y, nub $ drop x y)

findDupeOnHalves :: (String,String) -> Char
findDupeOnHalves (x,y) = findDupe x [y]

findDupeOnHeadTail :: [String] -> Char
findDupeOnHeadTail x = findDupe (head x) (tail x)

main :: IO ()
main = do
    contents <- readFile "3.txt"
    let split = lines contents
    let halfLengths = map (\x -> x `div` 2) $ map length split
    print $ sumValues $ map findDupeOnHalves $ map splitHalves $ zip halfLengths split
    print $ sumValues $ map findDupeOnHeadTail $ chunk 3 split

