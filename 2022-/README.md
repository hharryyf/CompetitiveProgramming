1. Integral Array [solved] (diff=1800, ad-hoc)
I'm actually quite amazed someone cannot solve this problem in contest, because I believe we've studied this technique for at least 10 times in the 2020 training :).
Just use the property of partial sum n/1 + n/2 + ... + n/n = O(nlogn), manipulate the y value, and also the quotient. https://codeforces.com/contest/1649/problem/D

2. Progressions Covering [solved] (diff=1900, greedy + any data structure)
The idea is too simple, just start from the right and use the range addition of arithmetic progression template.

3. Narrow Components [solved] (diff=2500, range tree, divide and conquer, union find)
The idea is exactly the same as https://codeforces.com/problemset/problem/811/E . I'm amazed someone can't solve it in contest. https://codeforces.com/contest/1661/problem/E

4. Potion Brewing Class [solved] (diff=2100, ad-hoc?)
It is a very simple problem, but I got wrong answer many times because of the place to take mod :(. https://codeforces.com/contest/1654/problem/D

5.  Lost Arithmetic Progression [solved] (diff=1900, ad-hoc)
Just manipulate the common difference of the sequence A. It must be a factor of the difference of C, and LCM(diff[A], diff[B]) = diff[C]
https://codeforces.com/contest/1673/problem/D

6 - 9 First rated div2 contest [A-D] [solved], https://codeforces.com/contest/1679

10. Traps [solved] (diff=1700, greedy)
https://codeforces.com/contest/1684/problem/D

11. 388535 [fail] (diff=2300, trie)
It is obvious that x = l ^ a[i] for some 1 <= i <= r - l + 1. Then, we just need to answer what's the minimum (resp. maximum) of a[i] ^ x and check if it is equal to l (resp. r).
https://codeforces.com/contest/1658/problem/D2

12. K-good [fail] (diff=1900, math)
Pattern finding? https://codeforces.com/contest/1656/problem/D

13. Tokitsukaze and Two Colorful Tapes [fail] (diff=1900, math + greedy)
The idea is to convert the permutation into the "graph". But the main obstacle is how to arange the numbers given the component size. The technique is to put the larger numbers at the increasing point,
and the smaller numbers at the decreasing points.


14. Staircases [fail] (diff=2100, ad-hoc?)
The key here is to realize we only need "maximal" staircases, which are stair cases that cannot be extended in either ends. With this observation, the problem can be solved easily. 
The reason I didn't solve it is mainly because I thought how to calculate the final answer using the simple dp way instead of this critical observation. The simple dp cannot be maintained 
within the correct time complexity. https://codeforces.com/contest/1598/problem/E


