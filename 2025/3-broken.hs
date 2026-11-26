import Data.List (sort, sortBy)

orderBySnd (ai, ae) (bi, be) = compare ae be

findMaxTwoInOrder :: String -> Int
findMaxTwoInOrder xs = do
    -- find the largest number that's NOT at the end of the string. then find the next largest number after the largest. if that fails, nested loop.
    -- this worked fine in python so dunno where the bug is here
    let (i,firstNum) = head $ reverse $ sortBy orderBySnd $ zip [0..] $ take ((length xs) - 1) xs
    let secondNum = head $ reverse $ sort $ drop (i + 1) xs
    read ([firstNum] ++ [secondNum]) :: Int

main :: IO ()
main = do
    contents <- readFile "3.txt"

    -- 1
    print $ sum $ map (\x -> findMaxTwoInOrder x) $ lines contents
