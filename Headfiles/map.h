#pragma once
#include"RBtree.h"
namespace my{
	template<class T1, class T2>
	class pair {
	public:
		T1 first;
		T2 second;
		pair() {
			first = T1();
			second = T2();
		}
		pair(const T1& val1, const T2& val2) {
			first = val1;
			second = val2;
		}
		pair(const pair& val) {
			first = val.first;
			second = val.second;
		}
		friend bool operator <(const pair& self,const pair& other) {
			return self.first < other.first;
		}
		friend bool operator >(const pair& self,const pair& other) {
			return self.first > other.first;
		}
		friend bool operator >=(const pair& self, const pair& other) {
			return self.first >= other.first;
		}
		friend bool operator <=(const pair& self, const pair& other) {
			return self.first <= other.first;
		}
		friend bool operator ==(const pair& self, const pair& other) {
			return self.first == other.first;
		}
		friend bool operator !=(const pair& self, const pair& other) {
			return !(self == other);
		}
	};
}

using namespace my;
template<class T1,class T2>
class _Iter {
public:
	typedef RBtreenode<my::pair<T1, T2>>* value_type;
	value_type val;
	_Iter() {
		val =NULL;
	}
	_Iter(const my::pair<T1, T2>& valp) {
		val = new value_type(valp);
	}
	_Iter(const value_type& valx) {
		val =valx;
	}
	_Iter(const _Iter& p) {
		val = p.val;
	}

	_Iter operator++() {
		if (val) {
			val = val->find_next();
		}
		return *this;
	}
	_Iter operator++(int) {
		_Iter p(*this);
		++*this;
		return p;
	}

	_Iter operator--() {
		if (val) {
			val = val->find_parent();
		}
		return *this;
	}
	_Iter operator--(int) {
		_Iter p(*this);
		--*this;
		return p;
	}
	my::pair<T1, T2>* operator ->() {
		return &val->value;
	}
	friend bool operator ==(const _Iter& self, const _Iter& other) {
		return self.val == other.val;
	}
	friend bool operator !=(const _Iter& self, const _Iter& other) {
		return self.val != other.val;
	}
};
template<class T1,class T2>
class map {
private:
	RBtree<my::pair<T1, T2>> intree;
public:
	typedef RBtreenode<my::pair<T1, T2>>*  treenode;
	typedef T1 key_type;
	typedef my::pair<T1, T2> value_type;
	typedef _Iter<T1,T2> iterator;

	my::pair<iterator, bool> insert(const value_type& val) {
		iterator rp = find(val.first);
		if (rp.val) {
			return my::pair<iterator, bool>(rp, false);
		}
		treenode sp=intree.insert(val);
		iterator p(sp);
		return my::pair<iterator, bool>(p, true);
	}
	iterator find(const T1& val1) {
		treenode p = intree.find(value_type(val1, T2()));
		if (p) {
			return iterator(p->value);
		}
		else {
			return end();
		}
	}
	T2& at(const T1& stvalue) {
		treenode p = intree.find(value_type(stvalue, T2()));
		if (p) {
			return p->value.second;
		}
		else {
			cout << "no such key_value!" << endl;
			T2 p = T2();
			return p;
		}
	}
	T2& operator [](const T1& stvalue) {
		treenode p = intree.find(value_type(stvalue, T2()));
		if (p) {
			return p->value.second;
		}
		else {
			p = intree.insert(value_type(stvalue, T2()));
			return p->value.second;
		}
	}
	int erase(const key_type& key) {
		int lsize = size();
		intree.erase(value_type(key, T2()));
		return lsize - size();

	}
	iterator erase(const iterator pos) {
		iterator res = pos++;
		intree.erase(pos.val);
		return res;
	}
	iterator erase(const iterator first, const iterator last) {
		iterator res = last++;
		for (iterator i = first, i != last, i++) {
			intree.erase(i.val);
		}
		return res;
	}
	size_t count(const key_type& key) const {
		if (find(key).val) {
			return 1;
		}
		else {
			return 0;
		}
	}
	iterator lower_bound(const key_type& key)//first >=key
	{
		iterator cur = find(key);
		return cur;
	}
	iterator upper_bound(const key_type& key)//first >key
	{
		iterator cur = find(key);
		cur++;
		return cur;
	}
	bool empty() {
		return size() <= 0;
	}
	void clear() {
		if (!empty()) {
			intree.clear(intree.root);
		}
	}
	size_t size() { return intree.size(); }
	iterator begin() {
		return iterator(intree.begin());
	}
	iterator end() {
		return iterator();
	}
};
