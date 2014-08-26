doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber x = if x < 100 then x * 2 else x

doubleSmallNumber' x = (if x > 100 then x else x*2) + 1

conanO'Brien = "It's a-me, Conan O'Brien!"

lostNumbers = [4,8,15,16,23,42]


factorial :: Integer -> Integer
factorial n = product [1..n]

f :: (Ord a) => a -> a -> Bool
f x y = x < y

lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

fib :: (Integral a) =>  Int -> a
fib 0 = 1
fib 1 = 1
fib n = fib(n - 1) + fib (n - 2)


fib' :: (Integral a) => Int -> a
fib' n
    | n == 0 = 1
    | n == 1 = 1
    | otherwise = fib'(n-1) + fib'(n-2)
