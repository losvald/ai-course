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

#ifndef LITERAL_H_
#define LITERAL_H_

#include <iostream>

#include "atom.h"

namespace logic {

template<class T>
class ExpressionElement;

template<class T>
class Literal {
public:
	typedef T IdType;
	typedef Atom<T> AtomType;
private:
	AtomType atom_;
	bool negated_;
public:
	static const Literal<T> TRUE;
	static const Literal<T> FALSE;

	Literal(AtomType atom, bool negated)
	: atom_(atom), negated_(negated) { }

	const AtomType& atom() const { return atom_; }

	bool isNegated() const { return negated_; }

	bool isNegated(const Literal& literal) const {
		return atom_ == literal.atom_
				&& (negated_ ^ literal.negated_);
	}

	bool isTautology() const {
		return (!negated_ && atom_.isTautology())
				|| (negated_ && atom_.isContradiction());
	}

	bool isContradiction() const {
		return (!negated_ && atom_.isContradiction())
				|| (negated_ && atom_.isTautology());
	}

	friend std::ostream& operator<<(std::ostream& os, const Literal& a) {
		if (a.isTautology())
			os << ' ' << '1';
		else if (a.isContradiction())
			os << ' ' << '0';
		else
			os << (a.isNegated() ? '~' : ' ') << a.atom();
		return os;
	}

	friend Literal operator!(const Literal& l) {
		return Literal(l.atom_, !l.negated_);
	}

	friend bool operator==(const Literal& a, const Literal& b) {
		return a.atom_ == b.atom_ && a.negated_ == b.negated_;
	}

	friend bool operator<(const Literal& a, const Literal& b) {
		return a.atom_ < b.atom_
				|| (!(b.atom_ < a.atom_) && (!a.negated_ && b.negated_));
	}
};

} // namespace logic


#endif /* LITERAL_H_ */
