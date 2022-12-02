import System.IO

desiredOutcomeToShape :: String -> String -> String
desiredOutcomeToShape them desiredOutcome
    | desiredOutcome == "R" = shapeThisBeats them
    | desiredOutcome == "S" = shapeBeatenBy them
    | otherwise = them

chooseShapesForDesiredOutcomes :: [[String]] -> [[String]]
chooseShapesForDesiredOutcomes =
    map (\(x:y:_) -> [x] ++ [(desiredOutcomeToShape x y)])

shapeBeatenBy :: String -> String
shapeBeatenBy x
    | x == "S" = "R"
    | x == "R" = "P"
    | x == "P" = "S"

shapeThisBeats :: String -> String
shapeThisBeats x
    | x == "R" = "S"
    | x == "P" = "R"
    | x == "S" = "P"

scoreOutcome :: [String] -> Int
scoreOutcome (them:me:_)
    | them == me = 3
    | them == shapeThisBeats me = 6
    | otherwise = 0

scoreShape :: String -> Int
scoreShape x
    | x == "R" = 1
    | x == "P" = 2
    | x == "S" = 3

normalizeShape :: String -> String
normalizeShape x
    | x == "X" || x == "A" = "R"
    | x == "Y" || x == "B" = "P"
    | x == "Z" || x == "C" = "S"

normalizeRound :: [String] -> [String]
normalizeRound = map normalizeShape

normalize :: [[String]] -> [[String]]
normalize = map normalizeRound

splitFileToRounds :: String -> [[String]]
splitFileToRounds contents = normalize $ map words $ lines contents

computeTotalScore :: [[String]] -> Int
computeTotalScore rounds = outcomeScore + shapeScore
    where
    myShapes = map head $ map tail $ rounds
    shapeScore = sum $ map scoreShape $ myShapes
    outcomeScore = sum $ map scoreOutcome $ rounds

main :: IO ()
main = do
    contents <- readFile "2.txt"
    let rounds = splitFileToRounds contents
    print $ computeTotalScore rounds
    print $ computeTotalScore $ chooseShapesForDesiredOutcomes rounds

