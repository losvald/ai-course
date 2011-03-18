/*
 *  Copyright (C) 2010 Leo Osvald <leo.osvald@gmail.com>
 *
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <iostream>
#include <fstream>

#include "backtrack_solver.h"

// driver program

using namespace std;

template<typename T, int R, int C>
istream& operator>>(istream& is, SudokuSolver<T, R, C>& solver) {
	static const int RC = R * C;
	for (int r = 0; r < RC; ++r)
		for (int c = 0; c < RC; ++c) {
			T val = 0;
			cin >> val;
			solver.set(r, c, val);
		}
	return is;
}

#if 0

int main() {
	SudokuSolver<int, 2> solver; // 2x2 sudoku
//	SudokuSolver<int, 2, 3> solver; // 2x3 sudoku
//	SudokuSolver<int, 3, 3> solver; // 3x3 sudoku
//	SudokuSolver<int, 4, 3> solver; // 4x3 sudoku
	cin >> solver;
	if (solver.solve())
		cout << solver;
	else
		cerr << "No valid solution exists" << endl;

	return 0;
}

#endif

/* Sample inputs

0 0 1 0
0 3 0 4
3 0 4 0
0 2 0 0

5 1 0 4 0 0
0 6 4 0 0 0
4 0 6 0 0 0
0 0 0 5 0 6
0 0 0 1 2 0
0 0 1 0 5 4

0 0 0 2 0 0 0 6 3
3 0 0 0 0 5 4 0 1
0 0 1 0 0 3 9 8 0
0 0 0 0 0 0 0 9 0
0 0 0 5 3 8 0 0 0
0 3 0 0 0 0 0 0 0
0 2 6 3 0 0 5 0 0
5 0 3 7 0 0 0 0 8
4 7 0 0 0 1 0 0 0

 0  0  0  0  0  0  0  0  1  0 11  0
12  7  0  1  3  9 10  0  6  0  0  4
 0 11  0  7  0  0 12  2  3 10  9  0
10  0  0  0  0  2  0  0  0  3  0  0
 0  4  0  0  0  0  3 12  8  5  1  9
 0  0  0  0  5  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  1  0  0  0  0
 1 12  5  8  6  3  0  0  0  0 10  0
 0  0  1  0  0  0  8  0  0  0  0  7
 0  2 12  3  1 11  0  0  9  0  4  0
 4  0  0  9  0  7 11  6 12  0  3  8
 0  3  0  6  0  0  0  0  0  0  0  0

*/

