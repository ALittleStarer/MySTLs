#pragma once
#include"common.h"
template<class T>
class queue {
private:
	T* data;
	int begin;
	int end;
	int nsize;
	int capacity;
public:
	queue();
	queue(const queue& father);
	~queue();
	int size() const { return nsize; }
	bool empty() { return nsize == 0; }
	T& front() { return data[begin]; }
	T& back() { return data[(end - 1) % capacity]; }
	void push(const T& value);
	void pop();
	void clear();
};

template<class T>
queue<T>::queue() {
	data = new T[1024];
	begin = 0;
	end = 0;
	nsize = 0;
	capacity = 1024;
}

template<class T>
queue<T>::queue(const queue<T>& father) {
	data = new T[father.capacity];
	nsize = father.nsize;
	for (int i = 0; i < nsize; i++) {
		data[i] = father.data[(father.begin + i) % father.capacity];
	}
	begin = 0;
	end = nsize;
	capacity = father.capacity;
}

template<class T>
queue<T>::~queue() {
	delete[]data;
}

template<class  T>
void queue<T>::push(const T& value) {
	if (nsize >= capacity) {
		T* ndata = new T[capa * 2];
		for (int i = 0; i < rsize; i++)
		{
			ndata[i] = data[i];
		}
		it = ndata + (it - data);
		delete[]data;
		data = ndata;
		capacity = capacity * 2;
	}
	data[end] = value;
	end = (end + 1) % capacity;
	nsize++;
}

template<class T>
void queue<T>::pop() {
	if (nsize > 0) {
		begin = (begin + 1) % capacity;
		nsize--;
	}
}
template<class T>
void queue<T>::clear() {
	begin = 0;
	end = 0;
	nsize = 0;
}

