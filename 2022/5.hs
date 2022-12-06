import Data.Char (isAlpha, isDigit)
import Data.List (transpose)

nonDigit :: Char -> Bool
nonDigit x = not $ isDigit x

nonEmpty :: String -> Bool
nonEmpty x = x /= ""

extractLeadingAlpha :: String -> String
extractLeadingAlpha = takeWhile isAlpha

hasLeadingAlpha :: String -> Bool
hasLeadingAlpha = isAlpha . head

extractNumbers :: String -> [Int]
extractNumbers [] = []
extractNumbers xs = do
    let afterDroppingNonDigits = dropWhile nonDigit xs
    let num = takeWhile isDigit afterDroppingNonDigits
    let afterDroppingNumber = dropWhile isDigit afterDroppingNonDigits
    if num == [] then []
    else [read num :: Int] ++ extractNumbers afterDroppingNumber

parseMovements :: [String] -> [[Int]]
parseMovements = map extractNumbers . tail . dropWhile nonEmpty

findStacksSegment :: [[Char]] -> [[Char]]
findStacksSegment = reverse . tail . reverse . takeWhile nonEmpty

parseStacks :: [String] -> [String]
parseStacks =
    map extractLeadingAlpha . filter hasLeadingAlpha .
    map reverse . transpose . findStacksSegment

setIndex :: Int -> a -> [a] -> [a]
setIndex index elem stacks =
    take index stacks ++ [elem] ++ drop (index + 1) stacks

move :: (String -> String) -> Int -> Int -> Int -> [String] -> [String]
move modelOperation count from to stacks = do
    let fromReversed = reverse (stacks!!from)
    let newFrom = reverse $ drop count fromReversed
    let newTo = (stacks!!to) ++ (modelOperation $ take count fromReversed)
    setIndex to newTo $ setIndex from newFrom stacks

applyMovements :: (String -> String) -> [String] -> [[Int]] -> [String]
applyMovements modelOperation stacks movements =
    foldl (\s (count:from:to:_) ->
        move modelOperation count (from - 1) (to - 1) s) stacks movements

main :: IO ()
main = do
    contents <- readFile "5.txt"
    let lns = lines contents
    let movements = parseMovements lns
    let stacks = parseStacks lns
    let model9000 = id
    let model9001 = reverse
    putStrLn . map last $ applyMovements model9000 stacks movements
    putStrLn . map last $ applyMovements model9001 stacks movements

