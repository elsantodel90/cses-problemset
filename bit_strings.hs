main = interact $ show . solve . read where solve n = (2^n) `mod` (10^9+7)
