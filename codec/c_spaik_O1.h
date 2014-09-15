const	UINT16	DATA_LENGTH = 578;

INT16	g_nOut[DATA_LENGTH];
INT16	g_nStep[DATA_LENGTH];
INT16	g_nCorr[DATA_LENGTH];

UINT16	nIndxDeCodSign;
INT16	g_nDeCodSign[DATA_LENGTH];


INT16	g_nIn[DATA_LENGTH] ={
37,
37,
62,
100,
100,
162,
162,
162,
75,
75,
50,
-12,
-12,
-75,
-200,
-200,
-312,
-312,
-287,
-150,
-150,
-50,
-50,
-50,
-62,
-87,
-87,
-25,
25,
25,
162,
162,
237,
312,
312,
300,
200,
200,
137,
150,
150,
75,
75,
-50,
-150,
-150,
-237,
-275,
-275,
-287,
-275,
-275,
-275,
-212,
-212,
-137,
-137,
-75,
-25,
-25,
37,
100,
100,
150,
225,
225,
275,
275,
225,
187,
187,
100,
62,
62,
112,
100,
100,
50,
-12,
-12,
-50,
-50,
-12,
50,
50,
150,
187,
187,
175,
150,
150,
37,
37,
-150,
-287,
-287,
-325,
-337,
-337,
-262,
-200,
-200,
-187,
-150,
-150,
-62,
-62,
62,
200,
200,
262,
175,
175,
-12,
-150,
-150,
-212,
-212,
-225,
-225,
-225,
-237,
-225,
-225,
-162,
-87,
-87,
-25,
75,
75,
100,
100,
87,
112,
112,
150,
162,
162,
200,
137,
137,
-12,
-12,
-237,
-325,
-325,
-300,
-212,
-212,
-137,
-62,
-62,
0,
62,
62,
75,
75,
125,
212,
212,
325,
325,
325,
312,
225,
225,
50,
50,
-150,
-337,
-337,
-462,
-475,
-475,
-337,
-175,
-175,
-100,
-87,
-87,
-62,
-62,
0,
75,
75,
100,
37,
37,
-25,
-12,
-12,
100,
100,
225,
312,
312,
337,
375,
375,
350,
287,
287,
112,
-50,
-50,
0,
0,
112,
212,
212,
200,
162,
162,
125,
100,
100,
25,
25,
-25,
-25,
-25,
0,
0,
0,
-12,
-50,
-50,
-137,
-125,
-125,
-87,
-87,
-37,
-25,
-25,
-75,
-112,
-112,
-100,
-87,
-87,
-75,
-75,
12,
125,
125,
150,
37,
37,
-87,
-175,
-175,
-187,
-175,
-175,
-150,
-150,
-137,
-137,
-137,
-87,
87,
87,
275,
362,
362,
300,
300,
350,
350,
350,
300,
137,
137,
50,
0,
0,
-25,
-50,
-50,
-50,
-50,
-50,
-87,
-87,
-175,
-200,
-200,
-175,
-100,
-100,
25,
25,
162,
412,
412,
562,
600,
600,
400,
137,
137,
-50,
-137,
-137,
-187,
-187,
-312,
-387,
-387,
-375,
-312,
-312,
-200,
-50,
-50,
25,
25,
150,
200,
200,
175,
162,
162,
275,
350,
350,
275,
50,
50,
-137,
-137,
-262,
-287,
-287,
-325,
-362,
-362,
-350,
-350,
-350,
-325,
-325,
-250,
-125,
-125,
12,
112,
112,
200,
275,
275,
300,
262,
262,
175,
175,
75,
-25,
-25,
-125,
-212,
-212,
-225,
-137,
-137,
-37,
-37,
12,
87,
87,
187,
175,
175,
150,
75,
75,
12,
12,
12,
0,
0,
-62,
-137,
-137,
-137,
-162,
-162,
-175,
-175,
-175,
-112,
-112,
-62,
-62,
-62,
-112,
-137,
-137,
-87,
-12,
-12,
-12,
-37,
-37,
62,
62,
150,
175,
175,
175,
87,
87,
-12,
-62,
-62,
-50,
-50,
-50,
-25,
-25,
-12,
50,
50,
37,
-62,
-62,
-200,
-212,
-212,
-137,
-137,
-137,
-100,
-100,
-62,
62,
62,
112,
137,
137,
112,
112,
12,
-112,
-112,
-262,
-337,
-337,
-300,
-175,
-175,
-87,
0,
0,
75,
75,
162,
237,
237,
237,
200,
200,
150,
150,
150,
125,
125,
0,
-62,
-62,
-37,
0,
0,
25,
50,
50,
37,
25,
25,
37,
37,
0,
25,
25,
150,
225,
225,
275,
312,
312,
375,
375,
350,
212,
212,
-12,
-175,
-175,
-225,
-275,
-275,
-325,
-275,
-275,
-212,
-212,
-100,
50,
50,
237,
337,
337,
262,
162,
162,
137,
137,
87,
-25,
-25,
-150,
-250,
-250,
-300,
-275,
-275,
-212,
-162,
-162,
-112,
-112,
-87,
-50,
-50,
12,
12,
12,
12,
50,
50,
75,
75,
12,
-37,
-37,
-125,
-225,
-225,
-287,
-325,
-325,
-325,
-325,
-325,
-287,
-287,
-200,
-50,
-50,
125,
250,
250,
350,
375,
375,
250,
250,
162,
125,
125,
62,
-62,
-62,
-175,
-212,
-212,
-212
};
