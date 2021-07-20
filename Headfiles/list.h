#pragma once
#include"common.h"

template<class T>
class list {
private:
	struct Node
	{
		T value;
		Node* previous;
		Node* next;
		Node(T myvalue) {
			value = myvalue;
			previous = NULL;
			next = NULL;
		}
		Node* push_back(T newvalue)
		{
			Node* p = new Node(newvalue);
			Node* h = this;
			while (h->next != NULL)
			{
				h = h->next;
			}
			p->previous = h;
			h->next = p;
			return p;
		}
		Node* push_front(T newvalue)
		{
			Node* p = new Node(newvalue);
			p->next = this;
			return p;
		}
	};
	Node* head;
	Node* tail;
	int nsize;
public:
	list();
	list(int n);
	list(int n, T value);
	list(int first, int last, list& fat);
	void push_back(T value);
	void push_front(T value);
	bool empty() { return nsize == 0; }
	void clear();
	void resize(int n);
	T& front();
	T& back();
	void pop_back();
	void pop_front();
	void reverse();
	void merge(list& p);
	void insert(int index, value);
	void insert(int index, int num, int value);
	void erase(int index);

};