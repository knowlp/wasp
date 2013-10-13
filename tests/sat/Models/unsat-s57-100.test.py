input = """
c generated by sgen
c see http://www.cs.qub.ac.uk/~i.spence/sgen
p cnf 57 124
-2 -3 -4 0
-1 -3 -4 0
-1 -2 -4 0
-1 -2 -3 0
-6 -7 -8 0
-5 -7 -8 0
-5 -6 -8 0
-5 -6 -7 0
-10 -11 -12 0
-9 -11 -12 0
-9 -10 -12 0
-9 -10 -11 0
-14 -15 -16 0
-13 -15 -16 0
-13 -14 -16 0
-13 -14 -15 0
-18 -19 -20 0
-17 -19 -20 0
-17 -18 -20 0
-17 -18 -19 0
-22 -23 -24 0
-21 -23 -24 0
-21 -22 -24 0
-21 -22 -23 0
-26 -27 -28 0
-25 -27 -28 0
-25 -26 -28 0
-25 -26 -27 0
-30 -31 -32 0
-29 -31 -32 0
-29 -30 -32 0
-29 -30 -31 0
-34 -35 -36 0
-33 -35 -36 0
-33 -34 -36 0
-33 -34 -35 0
-38 -39 -40 0
-37 -39 -40 0
-37 -38 -40 0
-37 -38 -39 0
-42 -43 -44 0
-41 -43 -44 0
-41 -42 -44 0
-41 -42 -43 0
-46 -47 -48 0
-45 -47 -48 0
-45 -46 -48 0
-45 -46 -47 0
-50 -51 -52 0
-49 -51 -52 0
-49 -50 -52 0
-49 -50 -51 0
-53 -54 -55 0
-53 -54 -56 0
-53 -54 -57 0
-53 -55 -56 0
-53 -55 -57 0
-53 -56 -57 0
-54 -55 -56 0
-54 -55 -57 0
-54 -56 -57 0
-55 -56 -57 0
12 3 24 0
53 3 24 0
53 12 24 0
53 12 3 0
16 40 57 0
18 40 57 0
18 16 57 0
18 16 40 0
30 22 52 0
44 22 52 0
44 30 52 0
44 30 22 0
7 45 42 0
55 45 42 0
55 7 42 0
55 7 45 0
20 5 29 0
9 5 29 0
9 20 29 0
9 20 5 0
47 21 35 0
17 21 35 0
17 47 35 0
17 47 21 0
39 41 10 0
34 41 10 0
34 39 10 0
34 39 41 0
50 11 46 0
13 11 46 0
13 50 46 0
13 50 11 0
37 48 4 0
32 48 4 0
32 37 4 0
32 37 48 0
19 25 51 0
56 25 51 0
56 19 51 0
56 19 25 0
6 2 33 0
49 2 33 0
49 6 33 0
49 6 2 0
26 43 1 0
15 43 1 0
15 26 1 0
15 26 43 0
8 38 27 0
23 38 27 0
23 8 27 0
23 8 38 0
54 14 36 0
54 14 31 0
54 14 28 0
54 36 31 0
54 36 28 0
54 31 28 0
14 36 31 0
14 36 28 0
14 31 28 0
36 31 28 0
"""

output = """
unsat
"""

timeout = 20
