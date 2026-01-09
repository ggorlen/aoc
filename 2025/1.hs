toInt xs = read xs :: Int

rotate a e =
    if tot == 0 then (tot, (snd a) + 1) else (tot, snd a)
    where
        prePreTot = (abs e) `mod` 100
        preTot = (fst a) + (if e < 0 then -prePreTot else prePreTot)
        tot = if preTot < 0 then 100 + preTot else (preTot `mod` 100)

main :: IO ()
main = do
    contents <- readFile "1.txt"
    let rots = foldl rotate (50, 0) $
          map (\(x, y) -> if x == 'R' then y else -y) $
          map (\x -> (head x, toInt $ tail x)) $ lines contents
    -- 1
    print $ snd rots
