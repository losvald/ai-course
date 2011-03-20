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

#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "../foreach.h"
#include "literal.h"

namespace logic {

template<class T>
class SubclauseIterator;

template<class T>
class Clause {
	typedef Literal<T> LiteralType;
	friend class SubclauseIterator<T>;

	std::set<LiteralType> literals_;
public:
	typedef const Clause* ConstPointer;

	void add(const LiteralType& literal) {
		if (literal.isTautology()) {
			literals_.clear();
			literals_.insert(Literal<T>::TRUE);
		} else if (!literals_.erase(!literal))
			literals_.insert(literal);
	}

	bool isNil() const { return literals_.empty(); }

	bool entails(const Clause& other) const {
		return std::includes(other.literals_.begin(), other.literals_.end(),
				literals_.begin(), literals_.end());
	}

	std::size_t size() const {
		return literals_.size();
	}

	bool isTautology() const {
		return size() == 1 && literals_.begin()->isTautology();
	}

	template<class Functor>
	void foreach(const Functor& f) const {
		FOREACH(it, literals_) {
			f(*it);
		}
	}

	SubclauseIterator<T> subclauseIterator() const;

	Clause() { }
	Clause(const Clause& clone) : literals_(clone.literals_) { }
	Clause(const LiteralType& literal) {
		add(literal);
	}

	friend std::ostream& operator<<(std::ostream& os, const Clause& clause) {
		bool first = true;
		FOREACH(it, clause.literals_) {
			if (first) {
				first = false;
			} else {
				os << ' ';
			}
			os << *it;
		}
		return os;
	}

	friend bool operator==(const Clause& a, const Clause& b) {
		return a.literals_ == b.literals_;
	}

	friend bool operator<(const Clause& a, const Clause& b) {
		return a.literals_ < b.literals_;
	}

	friend Clause operator|(const Clause& a, const Clause& b) {
		return Clause(a) |= b;
	}

	friend Clause operator+(const Clause& a, const Clause& b) {
		Clause ret = a;
		ret.literals_.insert(b.literals_.begin(), b.literals_.end());

		int complement_cnt = 0;
		__typeof(literals_.begin()) last = ret.literals_.begin();
		__typeof(last) cur = ++ret.literals_.begin();
		do {
			if (last->isNegated(*cur)) {
				(last = cur)++; // last = cur + 1
				ret.literals_.erase(cur);
				cur = last;
				ret.literals_.erase(--last);
				last = cur;

				// if two literals are complement to each other
				// then tautology is encountered
				if (++complement_cnt >= 2) {
					ret.literals_.clear();
					ret.literals_.insert(Literal<T>::TRUE);

					if (!ret.isTautology()) {
						std::cerr << "Fatal error: not tautology" << std::endl;
						exit(2);
					}

					return ret;
				}
			} else {
				last = cur++;
			}
		} while (cur != ret.literals_.end());

		if (complement_cnt != 1) {
			std::cerr << "Fatal error: " << complement_cnt << std::endl;
			exit(1);
		}

		return ret;
	}
};

/**
 * Iterator for iterating over subclauses. The order of iterating
 * is such that iteration starts with iterating over subclauses of size 1,
 * then 2 etc. Among subclauses of the same size, the order is lexicographical.
 */
template<class T>
class SubclauseIterator {
	Clause<T> clause_;
	bool* arr_;
	int subset_size_;
public:
	SubclauseIterator(const Clause<T>& clause)
	: clause_(clause), subset_size_(0) {
		arr_ = new bool[clause.size()];
		std::fill(arr_, arr_ + clause.size(), false);
	}

	~SubclauseIterator() {
		delete[] arr_;
	}

	Clause<T> next() {
		if (!std::next_permutation(arr_, arr_ + clause_.size())) {
			++subset_size_;
			std::fill(arr_, arr_ + clause_.size(), false);
			std::fill(arr_ + clause_.size() - subset_size_, arr_ + clause_.size(), true);
		}

		Clause<T> subclause;
		bool* cur = arr_;
		FOREACH(it, clause_.literals_) {
			if (*(cur++))
				subclause.literals_.insert(*it);
		}
		return subclause;
	}
};

template<typename T>
SubclauseIterator<T> Clause<T>::subclauseIterator() const {
	return SubclauseIterator<T>(*this);
}

} // namespace logic

#endif /* CLAUSE_H_ */
