import qualified Data.ByteString.Char8 as BS
import Data.Char

-- Confiamos en que Int sera de 64 bits porque la compu es de 64 bits.
-- Nota: Con Integer da TLE.

newtype Modu = Modu Int

p :: Int
p = 10^9 + 7

instance Num Modu where
    (Modu a) + (Modu b) = Modu $ (a+b) `mod` p
    (Modu a) * (Modu b) = Modu $ (a*b) `mod` p
    negate (Modu a) = Modu $ -a
    fromInteger = Modu . fromInteger
    abs _  = error "No sense in modular abs"
    signum = error "No sense in modular signum"
    
instance Show Modu where
    show (Modu a) = show a
    
calculate :: [Int] -> Modu
calculate [a,b] = Modu a ^ b

-- Usando feas CString en lugar de las String nativas porque son mucho mas eficientes y sino hay TLE

readInteger :: BS.ByteString -> Int
readInteger = BS.foldl' (\x c -> 10 * x + ord c - 48) 0

main = BS.interact $ BS.unlines  . map (BS.pack .show. calculate . map readInteger . BS.words) . tail . BS.lines
