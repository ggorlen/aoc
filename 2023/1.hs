import Data.Char (isDigit)
import qualified Data.Text as T

toInt xs = read xs :: Integer

-- part 1
findFirstDigit :: String -> Char
findFirstDigit = head . dropWhile (\x -> not $ isDigit x)

findFirstLastDigits :: String -> String
findFirstLastDigits xs =
    [findFirstDigit xs] ++ [findFirstDigit $ reverse xs]

totalFirstLastDigits :: [String] -> Integer
totalFirstLastDigits =
    sum . map toInt . map findFirstLastDigits

-- part 2
isPrefix :: String -> String -> Bool
isPrefix s = T.isPrefixOf (T.pack s) . T.pack

findFirstDigitWord :: String -> String
findFirstDigitWord xs =
    if isDigit $ head xs then [head xs]
    else if isPrefix "zero" xs then "0"
    else if isPrefix "one" xs then "1"
    else if isPrefix "two" xs then "2"
    else if isPrefix "three" xs then "3"
    else if isPrefix "four" xs then "4"
    else if isPrefix "five" xs then "5"
    else if isPrefix "six" xs then "6"
    else if isPrefix "seven" xs then "7"
    else if isPrefix "eight" xs then "8"
    else if isPrefix "nine" xs then "9"
    else findFirstDigitWord (tail xs)

findLastDigitWord :: String -> String
findLastDigitWord xs =
    if isDigit $ head xs then [head xs]
    else if isPrefix (reverse "zero") xs then "0"
    else if isPrefix (reverse "one") xs then "1"
    else if isPrefix (reverse "two") xs then "2"
    else if isPrefix (reverse "three") xs then "3"
    else if isPrefix (reverse "four") xs then "4"
    else if isPrefix (reverse "five") xs then "5"
    else if isPrefix (reverse "six") xs then "6"
    else if isPrefix (reverse "seven") xs then "7"
    else if isPrefix (reverse "eight") xs then "8"
    else if isPrefix (reverse "nine") xs then "9"
    else findLastDigitWord (tail xs)

findFirstLastDigitWords :: String -> String
findFirstLastDigitWords xs =
    (findFirstDigitWord xs) ++ (findLastDigitWord $ reverse xs)

totalFirstLastDigitWords :: [String] -> Integer
totalFirstLastDigitWords =
    sum . map toInt . map findFirstLastDigitWords

main :: IO ()
main = do
    contents <- readFile "1.txt"
    print $ totalFirstLastDigits $ lines contents
    print $ totalFirstLastDigitWords $ lines contents
