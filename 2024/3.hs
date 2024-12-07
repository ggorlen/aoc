-- TODO cleanup

import Data.Char (isDigit)
import Data.List (isPrefixOf)
import qualified Data.Text as T

splitToInts =
    map (\x -> read (T.unpack x) :: Int) . T.splitOn (T.pack ",") . T.pack

findMuls :: String -> Int
findMuls [] = 0
findMuls xs = do
    if isPrefixOf "mul(" xs then do
        let back = drop 4 xs
        let chunk = takeWhile (\x -> x /= ')') back

        if not $ all (\x -> isDigit x || x == ',') chunk then
            findMuls $ tail xs 
        else do
            let chunkBack = tail $ dropWhile (\x -> x /= ')') back
            findMuls chunkBack + (foldr (*) 1 $ splitToInts chunk)
    else findMuls $ tail xs

findMulsWithDo :: Bool -> String -> Int
findMulsWithDo enabled [] = 0
findMulsWithDo enabled xs = do
    if isPrefixOf "do()" xs then
        findMulsWithDo True $ tail xs
    else if isPrefixOf "don't()" xs then
        findMulsWithDo False $ tail xs
    else if (isPrefixOf "mul(" xs) && enabled then do
        let back = drop 4 xs
        let chunk = takeWhile (\x -> x /= ')') back

        if not $ all (\x -> isDigit x || x == ',') chunk then
            findMulsWithDo enabled $ tail xs 
        else do
            let chunkBack = tail $ dropWhile (\x -> x /= ')') back
            findMulsWithDo enabled chunkBack + (foldr (*) 1 $ splitToInts chunk)
    else findMulsWithDo enabled $ tail xs
    
main :: IO ()
main = do
    contents <- readFile "3.txt"
    print $ findMuls contents
    print $ findMulsWithDo True contents
