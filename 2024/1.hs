import qualified Data.Map.Strict as Map
import Data.List (nub, sort, transpose)

toInt xs = read xs :: Int

main :: IO ()
main = do
    contents <- readFile "1.txt"
    let cols = transpose $ map (\x -> map toInt $ words x) $ lines contents
    let (a:b:_) = map sort $ cols

    -- 1
    print $ sum $ map (\(a,b) -> abs $ a - b) $ zip a b

    -- 2
    let initialCounts = Map.empty :: Map.Map Int Int
    let counts = foldl (\acc e -> Map.insertWith (+) e 1 acc) initialCounts b
    print $ sum $ map (\x -> x * (Map.findWithDefault 0 x counts)) $ a
