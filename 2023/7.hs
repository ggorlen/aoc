import Data.List (elemIndex, group, nub, sort, sortBy)

nonSpace :: Char -> Bool
nonSpace x =  ' ' /= x

split :: String -> (String, Int)
split xs =
    (takeWhile nonSpace xs, read (dropWhile nonSpace xs) :: Int)

onLength :: String -> String -> Ordering
onLength x y = compare (length x) (length y)

groupCards :: String -> [String]
groupCards = sortBy onLength . group . sort

fiveOfAKind :: String -> Bool
fiveOfAKind xs = length (nub xs) == 1

fourOfAKind :: String -> Bool
fourOfAKind xs = length grouped == 2 && length (grouped!!0) == 1
    where grouped = groupCards xs

fullHouse :: String -> Bool
fullHouse xs = length grouped == 2 && length (grouped!!0) == 2
    where grouped = groupCards xs

threeOfAKind :: String -> Bool
threeOfAKind xs = length grouped == 3 && length (grouped!!2) == 3
    where grouped = groupCards xs

twoPair :: String -> Bool
twoPair xs =
    length grouped == 3 &&
    length (grouped!!1) == 2 &&
    length (grouped!!2) == 2
    where grouped = groupCards xs

onePair :: String -> Bool
onePair xs = length grouped == 4 && length (grouped!!3) == 2
    where grouped = groupCards xs

highCard :: String -> Bool
highCard xs = (length $ nub xs) == length xs

rankHand :: String -> Int
rankHand hand
    | fiveOfAKind hand = 7
    | fourOfAKind hand = 6
    | fullHouse hand = 5
    | threeOfAKind hand = 4
    | twoPair hand = 3
    | onePair hand = 2
    | highCard hand = 1
    | otherwise = 0

rankings :: String
rankings = "AKQJT98765432"

indexOf :: Eq a => a -> [a] -> Int
indexOf i xs = maybe (- 1) (+0) $ i `elemIndex` xs

breakTie :: String -> String -> Ordering
breakTie x y = do
    let (xx, yy) = head $ dropWhile (\(xx, yy) -> xx == yy) $ zip x y
    compare (indexOf yy rankings) (indexOf xx rankings)

rankHands :: (String, Int) -> (String, Int) -> Ordering
rankHands (x, _) (y, _) =
    if xr == yr then breakTie x y
    else compare xr yr
    where
        xr = rankHand x
        yr = rankHand y

solvePart1 :: [(String, Int)] -> Int
solvePart1 =
    sum . map (\(i, (_, bid)) -> bid * i) . zip [1..] . sortBy rankHands

main :: IO ()
main = do
    contents <- readFile "7.txt"
    let hands = map split $ lines contents
    print $ solvePart1 hands
