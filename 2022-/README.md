1. Integral Array (diff=1800, ad-hoc)
I'm actually quite amazed someone cannot solve this problem in contest, because I believe we've studied this technique for at least 10 times in the 2020 training :).
Just use the property of partial sum n/1 + n/2 + ... + n/n = O(nlogn), manipulate the y value, and also the quotient. https://codeforces.com/contest/1649/problem/D

2. Progressions Covering (diff=1900, greedy + any data structure)
The idea is too simple, just start from the right and use the range addition of arithmetic progression template.

3. Narrow Components (diff=2500, range tree, divide and conquer, union find)
The idea is exactly the same as https://codeforces.com/problemset/problem/811/E . I'm amazed someone can't solve it in contest. https://codeforces.com/contest/1661/problem/E

4. Potion Brewing Class (diff=2100, ad-hoc?)
It is a very simple problem, but I got wrong answer many times because of the place to take mod :(. https://codeforces.com/contest/1654/problem/D

5.  Lost Arithmetic Progression (diff=1900, ad-hoc)
Just manipulate the common difference of the sequence A. It must be a factor of the difference of C, and LCM(diff[A], diff[B]) = diff[C]
https://codeforces.com/contest/1673/problem/D

6 - 9 First rated div2 contest [A-D], https://codeforces.com/contest/1679

10. Traps (diff=1700, greedy)
https://codeforces.com/contest/1684/problem/D



