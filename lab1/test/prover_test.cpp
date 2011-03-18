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
#include <cstddef>
#include <cstring>

#include <cassert>

#include "../logic/prover.h"

using namespace std;
using namespace logic;

template<> const Atom<char> Atom<char>::TRUE('1');
template<> const Atom<char> Atom<char>::FALSE('0');
template<> const Literal<char> Literal<char>::TRUE(
		Atom<char>::TRUE, false);
template<> const Literal<char> Literal<char>::FALSE(
		Atom<char>::FALSE, false);

Literal<char> parseLiteral(char* token) {
	Literal<char> a('0', false);
	switch (token[0]) {
	case '0':
		a = Literal<char>::FALSE;
		break;
	case '1':
		a = Literal<char>::TRUE;
		break;
	case '~':
		a = Literal<char>(token[1], true);
		break;
	default:
		a = Literal<char>(token[0], false);
	}
	return a;
}

Clause<char> parseClause(char* str) {
	const char delimiters[] = " \t\n";
	char* token = strtok(str, delimiters);
	Clause<char> clause;
	while (token) {
		clause.add(parseLiteral(token));
		token = strtok(NULL, delimiters);
	}
	return clause;
}

void printSubclauses(const Clause<char>& clause) {
	SubclauseIterator<char> it(clause);
	cout << "Subclauses of " << clause << endl;
	while (true) {
		Clause<char> subclause = it.next();
		if (subclause.size() == clause.size())
			break;
		cout << subclause << endl;
	}
}

void inputClauses(Prover<char>& prover) {
	char buf[1024];
	while (cin.getline(buf, sizeof(buf))) {
		if (!strcmp(buf, "-"))
			break;
		bool prove = (buf[0] == ' ');
		if (prove) {
			Literal<char> l = parseLiteral(buf + prove);
			bool b = prover.prove(l);
			cout << "Holds: " << b << endl;
		} else {
			Clause<char> clause = parseClause(buf + prove);
			printSubclauses(clause);
			prover.addClause(clause);
		}
		cout << prover;
	}
}

#if 0
int main(int argc, char **argv) {
	Prover<char> s;
	inputClauses(s);
	cout << s << endl;

	return 0;
}

#endif

/*
a b
~a
 b

a b
~a
~b c
 c

a
b
~a ~c d
~b c
 d


*/

