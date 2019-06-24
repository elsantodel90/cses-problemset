main = interact $ show . sum . tail . takeWhile (/=0) . iterate (`div`5) . read
