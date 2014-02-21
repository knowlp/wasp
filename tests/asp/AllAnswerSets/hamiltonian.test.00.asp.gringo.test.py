input = """
1 2 2 1 3 4
1 3 2 1 2 4
1 4 0 0
1 5 2 1 6 7
1 6 2 1 5 7
1 7 0 0
1 8 2 1 9 10
1 9 2 1 8 10
1 10 0 0
1 11 2 1 12 13
1 12 2 1 11 13
1 13 0 0
1 14 2 1 15 16
1 15 2 1 14 16
1 16 0 0
1 17 2 1 18 19
1 18 2 1 17 19
1 19 0 0
1 20 2 1 21 22
1 21 2 1 20 22
1 22 0 0
1 23 2 1 24 25
1 24 2 1 23 25
1 25 0 0
1 26 2 1 27 28
1 27 2 1 26 28
1 28 0 0
1 29 2 1 30 31
1 30 2 1 29 31
1 31 0 0
1 32 2 1 33 34
1 33 2 1 32 34
1 34 0 0
1 35 2 1 36 37
1 36 2 1 35 37
1 37 0 0
1 38 2 1 39 40
1 39 2 1 38 40
1 40 0 0
1 41 2 1 42 43
1 42 2 1 41 43
1 43 0 0
1 44 2 1 45 46
1 45 2 1 44 46
1 46 0 0
1 47 2 1 48 49
1 48 2 1 47 49
1 49 0 0
1 50 2 1 51 52
1 51 2 1 50 52
1 52 0 0
1 53 2 1 54 55
1 54 2 1 53 55
1 55 0 0
1 56 2 1 57 58
1 57 2 1 56 58
1 58 0 0
1 59 2 1 60 61
1 60 2 1 59 61
1 61 0 0
1 62 2 1 63 64
1 63 2 1 62 64
1 64 0 0
1 65 2 1 66 67
1 66 2 1 65 67
1 67 0 0
1 68 2 1 69 70
1 69 2 1 68 70
1 70 0 0
1 71 2 1 72 73
1 72 2 1 71 73
1 73 0 0
1 74 2 1 75 76
1 75 2 1 74 76
1 76 0 0
1 77 2 1 78 79
1 78 2 1 77 79
1 79 0 0
1 80 2 1 81 82
1 81 2 1 80 82
1 82 0 0
1 83 2 1 84 85
1 84 2 1 83 85
1 85 0 0
1 86 2 1 87 88
1 87 2 1 86 88
1 88 0 0
1 89 2 1 90 91
1 90 2 1 89 91
1 91 0 0
1 92 2 1 93 94
1 93 2 1 92 94
1 94 0 0
1 95 2 1 96 97
1 96 2 1 95 97
1 97 0 0
1 98 2 1 99 100
1 99 2 1 98 100
1 100 0 0
1 101 2 1 102 103
1 102 2 1 101 103
1 103 0 0
1 104 2 1 105 106
1 105 2 1 104 106
1 106 0 0
1 107 2 1 108 109
1 108 2 1 107 109
1 109 0 0
1 110 2 1 111 112
1 111 2 1 110 112
1 112 0 0
1 113 2 1 114 115
1 114 2 1 113 115
1 115 0 0
1 116 2 1 117 118
1 117 2 1 116 118
1 118 0 0
1 119 2 1 120 121
1 120 2 1 119 121
1 121 0 0
1 122 2 1 123 124
1 123 2 1 122 124
1 124 0 0
1 125 2 1 126 127
1 126 2 1 125 127
1 127 0 0
1 128 1 0 17
1 129 1 0 20
1 130 2 0 128 2
1 129 2 0 128 8
1 131 2 0 128 5
1 130 2 0 129 50
1 131 2 0 129 53
1 128 2 0 129 47
1 128 2 0 130 17
1 129 2 0 130 20
1 128 2 0 131 29
1 132 2 0 131 35
1 129 2 0 131 32
1 131 2 0 132 59
1 1 2 0 2 8
1 1 2 0 2 5
1 1 2 0 5 2
1 1 2 0 5 8
1 1 2 0 8 2
1 1 2 0 8 5
1 1 2 0 17 20
1 1 2 0 20 17
1 1 2 0 29 35
1 1 2 0 32 29
1 1 2 0 32 35
1 1 2 0 35 29
1 1 2 0 35 32
1 1 2 0 47 50
1 1 2 0 47 53
1 1 2 0 50 53
1 1 2 0 50 47
1 1 2 0 53 50
1 1 2 0 53 47
1 1 2 0 2 50
1 1 2 0 5 53
1 1 2 0 5 59
1 1 2 0 8 32
1 1 2 0 8 20
1 1 2 0 17 101
1 1 2 0 17 92
1 1 2 0 17 47
1 1 2 0 17 29
1 1 2 0 20 8
1 1 2 0 20 116
1 1 2 0 20 32
1 1 2 0 29 17
1 1 2 0 29 47
1 1 2 0 32 8
1 1 2 0 32 20
1 1 2 0 47 17
1 1 2 0 47 29
1 1 2 0 50 2
1 1 2 0 53 59
1 1 2 0 53 5
1 1 2 0 59 53
1 1 2 0 59 5
1 1 1 1 128
1 1 1 1 128
1 1 1 1 128
1 1 1 1 128
1 1 1 1 128
1 1 1 1 130
1 1 1 1 130
1 1 1 1 130
1 1 1 1 130
1 1 1 1 131
1 1 1 1 131
1 1 1 1 131
1 1 1 1 131
1 1 1 1 131
1 1 1 1 131
1 1 1 1 129
1 1 1 1 129
1 1 1 1 129
1 1 1 1 129
1 1 1 1 132
1 1 1 1 132
1 1 1 1 132
1 1 1 1 132
0
128 reached(0)
129 reached(3)
130 reached(1)
131 reached(2)
132 reached(4)
3 out_hm(0,1)
6 out_hm(0,2)
9 out_hm(0,3)
12 out_hm(0,7)
15 out_hm(0,8)
18 out_hm(1,0)
21 out_hm(1,3)
24 out_hm(1,6)
27 out_hm(1,9)
30 out_hm(2,0)
33 out_hm(2,3)
36 out_hm(2,4)
39 out_hm(2,7)
42 out_hm(2,8)
45 out_hm(2,9)
48 out_hm(3,0)
51 out_hm(3,1)
54 out_hm(3,2)
57 out_hm(3,9)
60 out_hm(4,2)
63 out_hm(4,5)
66 out_hm(4,6)
69 out_hm(4,9)
72 out_hm(5,4)
75 out_hm(5,6)
78 out_hm(5,9)
81 out_hm(6,1)
84 out_hm(6,4)
87 out_hm(6,5)
90 out_hm(6,9)
93 out_hm(7,0)
96 out_hm(7,2)
99 out_hm(7,8)
102 out_hm(8,0)
105 out_hm(8,2)
108 out_hm(8,7)
111 out_hm(9,1)
114 out_hm(9,2)
117 out_hm(9,3)
120 out_hm(9,4)
123 out_hm(9,5)
126 out_hm(9,6)
2 in_hm(0,1)
5 in_hm(0,2)
8 in_hm(0,3)
11 in_hm(0,7)
14 in_hm(0,8)
17 in_hm(1,0)
20 in_hm(1,3)
23 in_hm(1,6)
26 in_hm(1,9)
29 in_hm(2,0)
32 in_hm(2,3)
35 in_hm(2,4)
38 in_hm(2,7)
41 in_hm(2,8)
44 in_hm(2,9)
47 in_hm(3,0)
50 in_hm(3,1)
53 in_hm(3,2)
56 in_hm(3,9)
59 in_hm(4,2)
62 in_hm(4,5)
65 in_hm(4,6)
68 in_hm(4,9)
71 in_hm(5,4)
74 in_hm(5,6)
77 in_hm(5,9)
80 in_hm(6,1)
83 in_hm(6,4)
86 in_hm(6,5)
89 in_hm(6,9)
92 in_hm(7,0)
95 in_hm(7,2)
98 in_hm(7,8)
101 in_hm(8,0)
104 in_hm(8,2)
107 in_hm(8,7)
110 in_hm(9,1)
113 in_hm(9,2)
116 in_hm(9,3)
119 in_hm(9,4)
122 in_hm(9,5)
125 in_hm(9,6)
0
B+
0
B-
1
0
1
"""
output = """
"""
