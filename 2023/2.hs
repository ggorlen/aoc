{-# LANGUAGE OverloadedStrings #-}

import qualified Data.Text as T
import Data.Char (isDigit)

toInt :: String -> Integer
toInt = read

split :: String -> String -> [String]
split sep = map T.unpack . T.splitOn (T.pack sep) . T.pack

parseCubes :: String -> [(Integer, String)]
parseCubes =
    map (\x -> (toInt (x!!1), x!!2)) . map (\x -> split " " x) . split ","

validDraw :: (Integer, String) -> Bool
validDraw (count, color) =
    if color == "blue" then count <= 14
    else if color == "red" then count <= 12
    else count <= 13

parseGameId :: String -> Integer
parseGameId =
    toInt . dropWhile (\x -> not (isDigit x)) . head . split ":"

parseGame :: String -> [[(Integer, String)]]
parseGame xs = do
    let game = head $ tail $ split ":" xs
    let sets = split ";" $ game
    map parseCubes sets

validGame :: String -> Bool
validGame = all (\xs -> all validDraw xs) . parseGame

maxOf color =
    foldr (\e a -> foldr (\e a -> if snd e == color then max (fst e) a else a) a e) 0

power :: [[(Integer, String)]] -> Integer
power game =
    maxOf "red" game * maxOf "blue" game * maxOf "green" game

solvePart1 :: [String] -> Integer
solvePart1 = sum . map parseGameId . filter validGame

solvePart2 :: [String] -> Integer
solvePart2 = sum . map power . map parseGame

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let lns = lines contents
    print $ solvePart1 lns
    print $ solvePart2 lns
