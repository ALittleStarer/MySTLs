#pragma once
#include"heap.h"
template<class T,typename pr=less<T>>
class priority_queue{
private:
	heap<T, pr> Heap;
	int nsize;
public:
	priority_queue();
	void push();
};
