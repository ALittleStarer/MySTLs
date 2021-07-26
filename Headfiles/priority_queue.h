#pragma once
#include"heap.h"
template<class T, typename pr = less<T>>
class priority_queue {
private:
	heap<T, pr> Heap;
	int nsize;
public:
	priority_queue();
	priority_queue(const priority_queue& father);
	~priority_queue() {}
	void push(const T& value);
	void pop();
	bool empty() { return nsize == 0; }
	int size() const { return nsize; }
	T& front();
	T& back();
	void clear() { Heap.clear(); }

};

template<class T, typename pr>
priority_queue<T, pr>::priority_queue() {
	nsize = 0;
}

template<class T, typename pr>
priority_queue<T, pr>::priority_queue(const priority_queue& father) {
	Heap = heap<T, pr>(father);
	nsize = father.nsize;
}
template<class T, typename pr>
void priority_queue<T, pr>::push(const T& value) {
	Heap.push(value);
	nsize++;
}

template<class T, typename pr>
void priority_queue<T, pr>::pop() {
	if (nsize > 0) {
		Heap.pop();
		nsize--;
	}
}

template<class T, typename pr>
T& priority_queue<T, pr>::front() {
	return Heap.top();
}

template<class T, typename pr>
T& priority_queue<T, pr>::back() {
	return Heap.back();
}

