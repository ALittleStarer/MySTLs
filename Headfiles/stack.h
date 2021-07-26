#pragma once
#include"common.h"
#include"list.h"
template<class T>
class stack {
private:
	list<T> stack_list;
	int nSize;
public:
	stack();
	stack(const list<T>& old);
	T& top();
	int size();
	void push(const T& value);
	void pop();
	bool empty();
	void swap(stack<T>& other);
	stack& operator =(stack& father);
};

template<class T>
stack<T>::stack() {
	stack_list = list<T>();
	nSize = 0;
}

template<class T>
stack<T>::stack(const list<T>& old) {
	stack_list = list<T>(old);
	nSize = old.nsize;
}
template<class T>
T& stack<T>::top() {
	return stack_list.front();
}

template<class T>
int stack<T>::size() {
	return nSize;
}

template<class T>
void stack<T>::push(const T& value) {
	stack_list.push_front(value);
	nSize++;
}

template<class T>
void stack<T>::pop() {
	stack_list.pop_front();
	nSize--;
}

template<class T>
bool stack<T>::empty() {
	return nSize == 0;
}

template<class T>
void stack<T>::swap(stack<T>& other) {
	stack_list.swap(other.stack_list);
	nSize = other.nSize;
}
template<class T>
stack<T>& stack<T>::operator =(stack<T>& father) {
	stack<T> newStack(father);
	return newStack;

}