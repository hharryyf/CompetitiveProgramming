# 2022 Problems


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


-- SWERC 2021 - 2022


15. Organizing SWERC [solved] (simulation)
https://codeforces.com/contest/1662/problem/A 

16. Bottle Arrangements [solved] (construction)
https://codeforces.com/contest/1662/problem/M

17. Boundary [solved] (math)
Just do some simple case work, time complexity O(T * sqrt(max(W, L))) https://codeforces.com/contest/1662/problem/H

18. Il Derby della Madonnina [solved] (range tree, dp)
dp[i] = max(dp[j] + 1 such that 0 <= j < i and |a[i] - a[j]| <= v * (t[i] - t[j])), which the condition is v * (t[j] - t[i]) <= a[i] - a[j] <= v * (t[i] - t[j]), v * t[j] + a[j] <= a[i] + v * t[i], and
v * t[j] - a[j] <= v * t[i] - a[i]. Thus we are asked the longest non-decreasing subsequence such that for (v * t[i] - a[i], v * t[i] + a[i])
https://codeforces.com/contest/1662/problem/L

19. Circular Maze [solved] (dfs)
The idea is to use the polar coordinate interpretation. We treat each 1-degree/1-radius region as a vertex, and treat the walls/circular walls as the edges we must delete.
Then, the question would be a very standard connectivity problem. https://codeforces.com/contest/1662/problem/O

20. Ice Cream Shop [solved] (sweep line)
For each hub, there's an interval that the people in the hub would buy ice-cream in the store if the store is in  such interval.
Find such interval for each hub using binary search, and use sweep line to do the task. https://codeforces.com/contest/1662/problem/I

21. Antennas [solved] (BFS, range tree)
Problems similar to this are CF605D and CF198E. Seems like in data structure at least, my problem solving ability is not too far away from state of art :)?
The idea is there are only a limited number of states but the number of edges in the graph is too many. We need to find nxt in BFS efficiently.
There are two possibilities: 1) nxt > curr 2) nxt < curr. Here > and < means compare the id of the state. We only explain case 1, because case 2 is dual.
For case 1, the idea is if i is connected to j (i < j), then i + p[i] >= j and j - p[j] <= i. Therefore, we maintain a range min tree such that each node stores i - p[i].
If a state is visited, we simply set its value to be INF. hen, at each state, we just find the minimum value also the position of the minimum value in the range [state id, min(N, state id + p[state id])]. Let's call it (val, pos). Then, if val < state, we can simply set dist[pos] = dist[state id] + 1 and also mark the state as visited. For case 2, just use a range max tree instead of range min tree.
One thing to note is when we mark a node as visited, we must update the position in both trees to be INF/-INF.
https://codeforces.com/contest/1662/problem/F


22. Evolution of Weasels [fail] (constriction)
The critical observation is every B can be moved to arbitrary places in the string, but not A and C. The relative order of A and C cannot be changed. Thus, the idea is to firstly move all Bs to the left,
and reduce 'AA' and 'CC'. https://codeforces.com/contest/1662/problem/D


23. Drone Photo [fail] (ad-hoc)
This problem is very technical. N=1500 makes me feel it's impossible to be data structure optimization, and it proves to be a correct guess. The idea is to calculate contribution, but the approach to it
is quite difficult to come up with. The idea is for each number we calculate how many numbers are less than it in the same row/same col. Let's represent these two quatities as row[i][j] and col[i][j].
Then, the answer is sum(row[i][j] * (N - 1 - col[i][j]) + col[i][j] * (N - 1 - row[i][j]), i=1..N, j=1..N) / 2. Why this is correct can be verified by drawing a few cases. https://codeforces.com/contest/1662/problem/N


24. Unique Occurrences [solved] (diff=2300,range tree, dynamic connectivity)
We consider the contribution of each edge (u, v, c). It is equal to the size of the component contains u times the size of the component contains v based on the forest with all the edges with color c removed. This changes the problem to a dynamic connectivity problem, add some edges, remove some edges, query the component size. Which can be solved with the range tree on query technique taught by Professor Ray Li. https://codeforces.com/contest/1681/problem/F

25. Yet Another Minimization Problem [solved] (diff=1800, dp)
We need to realize the optimized term is equal to (a[1] + a[2] + ... + a[n])^2 + (b[1] + b[2] + ... + b[n])^2 + (n-2) * (a[1]^2 + ... + a[n]^2 + b[1]^2 + ... + b[n]^2). Only the first two terms are
relevant to the order of the numbers. This transforms the problem to a simple dp. https://codeforces.com/contest/1637/problem/D

26. Best Pair [solved] (diff=2100, ad-hoc)
The observation is there are at most sqrt(N) many frequencies, we can group the numbers according to frequency, and then just brute force. https://codeforces.com/contest/1637/problem/E

27. Weight the Tree [solved] (diff=2000, ad-hoc, dp)
The idea is to realize unless N=2, there cannot be two adjacent nodes that are all good. Then, the problem reduces to the following: give a tree, no two nodes that are adjacent can be selected at the
same time. If a node is selected, the weight is deg[v], otherwise, the weight is 1. Find a set of valid selection such that the number of selected node is maximum, and among them choose the selection
that has the least sum of weight. It's a classic dp. https://codeforces.com/problemset/problem/1646/D

28. Take a Guess [solved] (diff=1800, ad-hoc)
The idea is we can solve x[1], x[2], x[3] based on the query result of x[1] & x[2], x[1] | x[2], x[1] & x[3], x[1] | x[3], x[3] & x[2], x[3] | x[2]. After that, we can know x[4] to x[n] based on
queries like x[1] | x[i], x[1] & x[i]. https://codeforces.com/contest/1556/problem/D

29. Not Adding [solved] (diff=1900, ad-hoc, number theory)
The idea is to check if each of 1 to 1e6 can be the gcd of some subset of the numbers in the array. To do this, we can calculate the gcd of all numbers that are a multiple of i for each i=1..1e6.
If the gcd is equal to i, then i can be formed. https://codeforces.com/contest/1627/problem/D

