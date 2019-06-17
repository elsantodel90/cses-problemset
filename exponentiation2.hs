import qualified Data.ByteString.Char8 as BS
import Data.Char

-- Confiamos en que Int sera de 64 bits porque la compu es de 64 bits.
-- Nota: Con Integer da TLE.

p :: Int
p = 10^9+7

potlog :: Int -> Int -> Int -> Int
potlog a 0 m = 1
potlog a b m | odd b     = (a * r) `mod` m
             | otherwise = r
                where a2 = (a*a) `mod` m
                      r  = potlog a2 (b`div`2) m

calculate :: [Int] -> Int
calculate [0,b,c] | b == 0 && c /= 0 = 1
                  | otherwise        = 0
calculate [a,b,c] = potlog a (potlog b c (p-1)) p

-- Usando feas CString en lugar de las String nativas porque son mucho mas eficientes y sino hay TLE

readInteger :: BS.ByteString -> Int
readInteger = BS.foldl' (\x c -> 10 * x + ord c - ord '0') 0

main = BS.interact $ BS.unlines  . map (BS.pack .show. calculate . map readInteger . BS.words) . tail . BS.lines
