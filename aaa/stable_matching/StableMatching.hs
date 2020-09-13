import Data.List

--Stable Matching problem

-- Men's preferences, 

{- men_pref = [[4,3,1,2],
			   [2,3,1],
			   [3,2,1]]

-}

-- Women's preferences.
{- women_pref = [[1,2,3],
			     [2,3,1],
			     [3,2,1]]

-}

-- Couples     m w
{- couples = [(1,2),
			  (3,3),
			  (2,1),
			  (4,4),
			  (5,5)]
-}

-- Checks wether engagement should be done.
-- 				          Mn prf,  Wmn prf,  Curr,    M      W
engage :: [[Int]] -> [[Int]] -> [(Int,Int)] -> Int -> Int -> Bool
engage men_pref women_pref couples m_idx w_idx =
    if lookUpPos (men_pref !! m_idx) w_idx > lookUpPos --men is
        then
            True
        else 
            False

--Returns position of given element in list.
lookUpPos :: [Int] -> Int -> Int
lookUpPos [] n = -1
lookUpPos (x:xs) n 
    | not (n == x) = 1 + lookUpPos xs n
    | otherwise = 0

-- Receives list of tuples and a value, and returns second of the pair containing val.
lookUpPair :: [(Int, Int)] -> Int -> Int 
lookUpPair [] n = -1
lookUpPair (x:xs) n
    | (n == (fst x)) = snd x
    | otherwise = lookUpPair xs n

--sortListTuplesByFirst :: (Ord a) => [(a,a)] -> [(a,a)]

{- Implement sort
couple_sort :: (Int a) => [(a,a)] -> [(a,a)]
-- Implement sort using pair first element.
-}
-- Collect input data
-- While single men and 

main = putStrLn "maoe"
