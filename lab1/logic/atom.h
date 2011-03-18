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

#ifndef ATOM_H_
#define ATOM_H_

namespace logic {

template<class T>
class Atom {
	T id_;
public:
	typedef T IdType;
	static const Atom<T> TRUE;
	static const Atom<T> FALSE;

	Atom(const T& id) : id_(id) { }
	const T& id() const { return id_; }
	bool isTautology() const {
		return id_ == Atom::TRUE.id_;
	}
	bool isContradiction() const {
		return id_ == Atom::FALSE.id_;
	}
	friend bool operator==(const Atom& a, const Atom& b) {
		return a.id_ == b.id_;
	}
	friend bool operator<(const Atom& a, const Atom& b) {
		return a.id_ < b.id_;
	}
	friend std::ostream& operator<<(std::ostream& os, const Atom& a) {
		if (a.isTautology())
			os << '1';
		else if (a.isContradiction())
			os << '0';
		else
			os << a.id_;
		return os;
	}
};

} // namespace logic

#endif /* ATOM_H_ */
